#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <RGB.h>
#include <Html.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);

String responseHTML = ""
                      "<!DOCTYPE html><html lang='en'><head>"
                      "<meta name='viewport' content='width=device-width'>"
                      "<title>CaptivePortal</title></head><body>"
                      "<h1>Hello World!</h1><p>This is a captive portal example."
                      " All requests will be redirected here.</p></body></html>";


#define WIFI_SSID "Ultimaker Robot"// SSID
#define WIFI_KEY  "12345678"   // KEY


#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

Servo LinearActor;
Servo Arm;

byte Steering_PWM_PIN = D6;
byte Speed_PWM_PIN = D8;
byte RobotDispenser_PWM_PIN = D0;

#define Matrix_PIN 3
#define NUMPIXELS 64
#define BRIGHTNESS 96

#define mw 8
#define mh 8

Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, Matrix_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

int steering_pwm_value;
int speed_pwm_value;

int Trigger_PWM_Min = 1088;
int Trigger_PWM_Max = 1924;

int Speed_PWM_Min = 1088;
int Speed_PWM_Max = 1924;

int Steering_PWM_Min = 1088;
int Steering_PWM_Max = 1924;

int PWMA=5;//Right side
int PWMB=4;//Left side
int DA=0;//Right reverse
int DB=2;//Left reverse

int MotorKickStartService = 1;
int MotorKickstartA = 0;
int MotorKickstartB = 0;
int KickStartLevel = 150;
int KickStartThreshold = 60;
int BottomKickStartThreshold = 50;
int KickStartTime = 40;

unsigned long KickAStartMillis;
unsigned long KickBStartMillis;

unsigned long DispenseProcessStartMillis;
unsigned long DispenserCooldown = 1000;
int DispenseProcess = 0;
int ArmUp = 0;
int i;
int TriggerPressed = 0;

void RC_Controll(){
 steering_pwm_value = pulseIn(Steering_PWM_PIN, HIGH, 20000);
 speed_pwm_value = pulseIn(Speed_PWM_PIN, HIGH, 20000);
 Serial.print(steering_pwm_value);
 Serial.print(" : ");
 Serial.print(speed_pwm_value);
 if(steering_pwm_value < 100){
  steering_pwm_value = Steering_PWM_Min + ((Steering_PWM_Max - Steering_PWM_Min)/2);
}
if(speed_pwm_value < 100){
  speed_pwm_value = Speed_PWM_Min + ((Speed_PWM_Max - Speed_PWM_Min)/2);
}
 Serial.print(" : ");
 Serial.print(steering_pwm_value);
 Serial.print(" : ");
 Serial.print(speed_pwm_value);

 int Speed = map(speed_pwm_value, Speed_PWM_Min, Speed_PWM_Max, -255, 255);
 int Steering = map(steering_pwm_value, Steering_PWM_Min, Steering_PWM_Max, -255, 255);

 if(Speed <= 10 && Speed >= -10){
  Speed = 0;
 }
 if(Steering <= 10 && Steering >= -10){
  Steering = 0;
 }
 /*
 Serial.print(steering_pwm_value);
 Serial.print(" : ");
 Serial.print(speed_pwm_value);
 Serial.print(" : ");
 Serial.println(Speed);
*/

 int SpeedA = map(speed_pwm_value, Speed_PWM_Min, Speed_PWM_Max, -255, 255) + map(steering_pwm_value, Steering_PWM_Min, Steering_PWM_Max, 255, -255);
 int SpeedB = map(speed_pwm_value, Speed_PWM_Min, Speed_PWM_Max, -255, 255) + map(steering_pwm_value, Steering_PWM_Min, Steering_PWM_Max, -255, 255);

 if(SpeedA >= 0){
  digitalWrite(DA, HIGH);
 }else{
  digitalWrite(DA, LOW);
  SpeedA = SpeedA * -1;
 }
 if(SpeedB >= 0){
  digitalWrite(DB, HIGH);
 }else{
  digitalWrite(DB, LOW);
  SpeedB = SpeedB * -1;
 }

if(MotorKickstartA == 0 && SpeedA >= KickStartThreshold && MotorKickStartService == 1){
  analogWrite(PWMA, KickStartLevel);
  KickAStartMillis = millis();
  Serial.println("KickA");
  MotorKickstartA = 1;
 }
 if(MotorKickstartB == 0 && SpeedB >= KickStartThreshold && MotorKickStartService == 1){
  analogWrite(PWMB, KickStartLevel);
  KickBStartMillis = millis();
  Serial.println("KickB");
  MotorKickstartB = 1;
 }

 if(millis() - KickAStartMillis > KickStartTime){
   analogWrite(PWMA, SpeedA);
 }
 if(millis() - KickBStartMillis > KickStartTime){
   analogWrite(PWMB, SpeedB);
 }

if(MotorKickstartA == 1 && SpeedA <= BottomKickStartThreshold){
  MotorKickstartA = 0;
 }
 if(MotorKickstartB == 1 && SpeedB <= BottomKickStartThreshold){
  MotorKickstartB = 0;
 }
}



void WiFi_Setup() {
  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft access point mode");
  WiFi.softAP(WIFI_SSID, WIFI_KEY);
  WiFi.setSleep(false);
  IPAddress IP = WiFi.softAPIP();
  MDNS.begin("BSS");
  Serial.println();
  Serial.println("MasterServer started.");
  Serial.print("IP address: ");
  Serial.println(IP);
  Serial.println("MAC:" + WiFi.macAddress());
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(Steering_PWM_PIN, INPUT);
pinMode(Speed_PWM_PIN, INPUT);
pinMode(RobotDispenser_PWM_PIN, INPUT);
pinMode(PWMA, OUTPUT);
pinMode(PWMB, OUTPUT);
pinMode(DA, OUTPUT);
pinMode(DB, OUTPUT);
LinearActor.attach(D5, 500, 2400);
Arm.attach(D7, 500, 2400);
/*
matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
    display_rgbBitmap(0);
*/
   WiFi_Setup();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
RC_Controll();
Serial.println(analogRead(A0));
int DispenserPWM = pulseIn(RobotDispenser_PWM_PIN, HIGH, 20000);
if(DispenserPWM < 100){
  DispenserPWM = Trigger_PWM_Min + ((Trigger_PWM_Max - Trigger_PWM_Min)/2);
}
if(DispenserPWM > 1600 && TriggerPressed == 0 && analogRead(A0) <= 200){
  TriggerPressed = 1;
  if(DispenseProcess == 0 && millis() - DispenseProcessStartMillis > DispenserCooldown){
    DispenseProcessStartMillis = millis();
  DispenseProcess = 1;
  i = 0;
  }
  if(ArmUp == 1){
  i = 3;
  }
}else{
if(DispenserPWM < 1200 && TriggerPressed == 1){
  TriggerPressed = 0;
}
}

if(DispenseProcess == 1){
    if(i == 0){
      LinearActor.write(0);
      i++;
    }
    if(millis() - DispenseProcessStartMillis >= 2000 && i == 1){
      LinearActor.write(135);
       i++;
    }
    if(millis() - DispenseProcessStartMillis >= 4000 && i == 2){
      Arm.write(0);
      ArmUp = 1;
    }
    if(millis() - DispenseProcessStartMillis >= 6000 && i == 3){
      Arm.write(90);
      ArmUp = 0;
      i++;
    }
    if(i == 4){
      DispenseProcess = 0;
    }
}

}




/*
// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    uint16_t RGB_bmp_fixed[w * h];
    for (uint16_t pixel=0; pixel<w*h; pixel++) {
  uint8_t r,g,b;
  uint16_t color = pgm_read_word(bitmap + pixel);

  //Serial.print(color, HEX);
  b = (color & 0xF00) >> 8;
  g = (color & 0x0F0) >> 4;
  r = color & 0x00F;
  //Serial.print(" ");
  //Serial.print(b);
  //Serial.print("/");
  //Serial.print(g);
  //Serial.print("/");
  //Serial.print(r);
  //Serial.print(" -> ");
  // expand from 4/4/4 bits per color to 5/6/5
  b = map(b, 0, 15, 0, 31);
  g = map(g, 0, 15, 0, 63);
  r = map(r, 0, 15, 0, 31);
  //Serial.print(r);
  //Serial.print("/");
  //Serial.print(g);
  //Serial.print("/");
  //Serial.print(b);
  RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
  //Serial.print(" -> ");
  //Serial.println(RGB_bmp_fixed[pixel], HEX);
    }
    matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}

void display_bitmap(uint8_t bmp_num, uint16_t color) {
    static uint16_t bmx,bmy;

    // Clear the space under the bitmap that will be drawn as
    // drawing a single color pixmap does not write over pixels
    // that are nul, and leaves the data that was underneath
    matrix->fillRect(bmx,bmy, bmx+8,bmy+8, LED_BLACK);
    matrix->drawBitmap(bmx, bmy, mono_bmp[bmp_num], 8, 8, color);
    bmx += 8;
    if (bmx >= mw) bmx = 0;
    if (!bmx) bmy += 8;
    if (bmy >= mh) bmy = 0;
    matrix->show();
}

void display_rgbBitmap(uint8_t bmp_num) {
    static uint16_t bmx,bmy;

    fixdrawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 8, 8);
    bmx += 8;
    if (bmx >= mw) bmx = 0;
    if (!bmx) bmy += 8;
    if (bmy >= mh) bmy = 0;
    matrix->show();
}*/

//============================================================================================
//=====================================WEBSERVER==============================================
//============================================================================================
void handleRoot() {
  Serial.println("Enter handleRoot");
  String header;

    Serial.println(server.uri());
    if (server.uri() != "/") {
      server.sendHeader("Location", "/basics");
      server.sendHeader("Cache-Control", "no-cache");
      server.send(301);
      return;
    }

}


/*
bool is_authentified() {
  Serial.println("Enter is_authentified");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    } else {
      Serial.println("Authentification Failed");
      return false;
    }

  }
}

void handleLogin() {
  String msg;
  get_login_string(&web_login, msg);
  if (server.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
  }
  else if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == "admin" &&  server.arg("PASSWORD") == "admin" ) {
      server.sendHeader("Location", "/basics");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      Serial.println("Log in Successful");
    }
    else {
      msg = "Wrong username/password! try again.";
      Serial.println("Log in Failed");
      server.send(200, "text/html", web_login);
    }
  }

  else if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (is_authentified()) {
      Serial.println("Login");
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.send(301);
    }
    else {
      server.send(200, "text/html", web_login);
    }
  }
  else {
    server.send(200, "text/html", web_login);
  }
}
*/
void handleBasics() {
    server.send(200, "text/html", web_basics);

}
/*
void handleDMX() {
  if (is_authentified()) {
    server.send(200, "text/html", web_dmx);
  } else {
    send_login();
  }
}

void handleActions() {
  if (is_authentified()) {
    server.send(200, "text/html", web_actions);
  } else {
    send_login();
  }
}

void send_login() {
  server.sendHeader("Location", "/login");
  server.sendHeader("Cache-Control", "no-cache");
  server.send(301);
}

/*void update_audio() {
  PressedAudio = int_string_to_int(preferences.getString("BPS"));
  RightAudio   = int_string_to_int(preferences.getString("RAS"));
  WrongAudio   = int_string_to_int(preferences.getString("WAS"));
}

void update_web_strings() {
  updateBasics();
  updateActions();
  updateDMX();
}

void updateBasics() {
  get_basics_string(&web_basics, preferences.getString("quiz_type"), preferences.getString("PWNPR"), preferences.getString("PCSD"), preferences.getString("PPMT"));
}

void updateActions() {
  get_action_string(&web_actions, preferences.getString("PPC"), preferences.getString("OPC"), preferences.getString("BPS"), preferences.getString("PBBUK"), preferences.getString("RPPC"), preferences.getString("ROPC"), preferences.getString("RAS"), preferences.getString("RABUK"), preferences.getString("WPPC"), preferences.getString("WOPC"), preferences.getString("WAS"), preferences.getString("WABUK"), preferences.getString("SColor"), preferences.getString("DPC"), preferences.getString("RBUK"));
}

void updateDMX() {
  get_dmx_string(&web_dmx, preferences.getString("NOL"), preferences.getString("SC"), preferences.getString("CPL"), preferences.getString("Bright"), preferences.getString("Red"), preferences.getString("Green"), preferences.getString("Blue"), preferences.getString("White"));
}

void handleSaveSettings() {
  if (server.hasArg("quiz_type")) {
    preferences.putString("quiz_type", server.arg("quiz_type"));
    preferences.putString("PWNPR", bool_to_string(server.hasArg("PlayerWrongNextPlayserbyReset")));
    preferences.putString("PCSD", bool_to_string(server.hasArg("PlayersCanSeeDelays")));
    preferences.putString("PPMT", bool_to_string(server.hasArg("PlayersPressMultipleTimes")));
    preferences.putString("TLPGTLC", bool_to_string(server.hasArg("ToLatePlayersGetToLateColor")));
    preferences.putString("OPPGAC", bool_to_string(server.hasArg("OnlyPressedPlayerGetAnswerColor")));
    ShowTolate = string_to_bool(preferences.getString("PCSD"));
    updateBasics();
    server.sendHeader("Location", "/basics");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
  }
  else if (server.hasArg("PressedPlayerColor")) {
    preferences.putString("PPC", server.arg("PressedPlayerColor"));
    preferences.putString("OPC", server.arg("OtherPlayersColor"));
    preferences.putString("BPS", server.arg("BuzzerPressedSound"));
    preferences.putString("PBBUK", server.arg("PressedBuzzerBadUsbKey"));
    preferences.putString("RPPC", server.arg("RightPressedPlayerColor"));
    preferences.putString("ROPC", server.arg("RightOtherPlayersColor"));
    preferences.putString("RAS", server.arg("RightAnswerSound"));
    preferences.putString("RABUK", server.arg("RightAnswerBadUsbKey"));
    preferences.putString("WPPC", server.arg("WrongPressedPlayersColor"));
    preferences.putString("WOPC", server.arg("WrongOtherPlayersColor"));
    preferences.putString("WAS", server.arg("WrongAnswerSound"));
    preferences.putString("WABUK", server.arg("WrongAnswerBadUsbKey"));
    preferences.putString("SColor", server.arg("StandbyColor"));
    preferences.putString("DPC", server.arg("DeactivatedPlayersColor"));
    preferences.putString("RBUK", server.arg("ResetBadUsbKey"));
    update_audio();
    if (server.arg("PlayBuzzerPressedSound") == "Play") {
      play_audio(PressedAudio, NumberOfPressedAudios, PressedFolder);
    } else if (server.arg("PlayRightAnswerSound") == "Play") {
      play_audio(RightAudio, NumberOfRightAudios, RightAnswerFolder);
    } else if (server.arg("PlayWrongAnswerSound") == "Play") {
      play_audio(WrongAudio, NumberOfWrongAudios, WrongAnswerFolder);
    }
    updateActions();
    server.sendHeader("Location", "/actions");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
  }
  else if (server.hasArg("NumberOfLights")) {
    preferences.putString("NOL", server.arg("NumberOfLights"));
    preferences.putString("SC", server.arg("StartChannel"));
    preferences.putString("CPL", server.arg("ChannelPerLight"));
    preferences.putString("Bright", server.arg("Brightness"));
    preferences.putString("Red", server.arg("Red"));
    preferences.putString("Green", server.arg("Green"));
    preferences.putString("Blue", server.arg("Blue"));
    preferences.putString("White", server.arg("White"));
    updateDMX();
    server.sendHeader("Location", "/dmx");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
  }
  //Serial.println(server.hasArg("quiz_type"));
}
*/
void StartWebserver() {
  server.on("/", handleRoot);
  server.on("/generate_204", handleRoot); //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/connectivitycheck.gstatic.com", handleRoot); //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  //server.on("/fwlink", handleRoot);
  //server.on("/nmcheck.gnome.org", handleRoot);
  /*
  server.on("/login", handleLogin);

  server.on("/actions", handleActions);
  server.on("/dmx", handleDMX);
  server.on("/save", handleSaveSettings);
  */
  server.onNotFound(handleRoot);
  server.on("/basics", handleBasics);

  //update_web_strings();
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);

  server.begin();
}
