#include "Arduino.h"
#include "RGB.h"
#include "Wire.h"
#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include "EEPROM.h"
//#include <DNSServer.h>
#include <Servo.h>
#include "Html.h"
#include "RunAt.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Web-Interface

ESP8266WebServer server(80);

#define WIFI_SSID "Ultimaker_Robot"
#define WIFI_KEY "adminadmin"
#define CHANNEL 1
#define HIDDEN false
#define MAX_CONNECTION 10

// NeoPixels

byte pagebuffer[222] = {};  // 700

#define NEO_PIXELS_PIN 3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(74, NEO_PIXELS_PIN, NEO_GRB + NEO_KHZ800);


//############################################################
//######################Servo Variables#######################
//############################################################

Servo LinearActor;
Servo Arm;

byte Steering_PWM_PIN = D6;
byte Speed_PWM_PIN = D7;
byte RobotDispenser_PWM_PIN = D0;

int steering_pwm_value;
int speed_pwm_value;

int Trigger_PWM_Min = 1088;
int Trigger_PWM_Max = 1924;

int Speed_PWM_Min = 1088;
int Speed_PWM_Max = 1924;

int Steering_PWM_Min = 1088;
int Steering_PWM_Max = 1924;

int PWMA = 5; //Right side
int PWMB = 4; //Left side
int DA = 0; //Right reverse
int DB = 2; //Left reverse

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

// Init WebServer

void handle_save_settings() {
  current_page = server.arg("page_setter").toInt() -1;
  for (uint8_t i = 0; i < 74; i++) {
    page[current_page][i] = rgb_hex_string_to_rgb(server.arg(("neopx_" + String(i))));
  }

  update_html_string();
  NeoPixels_Write_All(current_page);

  Serial.println(gen_c_array(current_page));

  server.sendHeader("Location", "/");
  server.sendHeader("Cache-Control", "no-cache");
  server.send(301);

  write_buffer(current_page);
}

void handle_root() {
  server.send(200, "text/html", html);
}

void init_web_server() {
  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft access point mode");
  WiFi.softAP(WIFI_SSID, WIFI_KEY, CHANNEL, HIDDEN, MAX_CONNECTION);

  Serial.println();
  Serial.println("Starting WebServer ...");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("MAC:" + WiFi.macAddress());

  server.on("/", handle_root);
  server.on("/save", handle_save_settings);
  server.begin();

  Serial.println("Started WebServer");
}

// NeoPixels

void NeoPixels_Write(uint16_t n, rgb *RGB) {
  pixels.setPixelColor(n, RGB->red, RGB->green, RGB->blue);
}

void NeoPixels_Write_All(uint16_t n) {
  int p = 0;
  for (uint16_t j = 0; j <= 7; j++) {
    for (int16_t i = 7; i >= 0;--i) {
      NeoPixels_Write(((i*8)+j),&page[n][p+10]);
      p++;
    }
  }
  pixels.show();
}


// EEPROM Stuff

void write_buffer(uint8_t n) {
    uint8_t x = 0;
    for (uint8_t i = 0; i < 74; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            if (j == 0) {
                pagebuffer[x] = page[n][i].red;
            } else if (j == 1) {
                pagebuffer[x] = page[n][i].green;
            } else {
                pagebuffer[x] = page[n][i].blue;
            }
            x++;
        }
    }
    write_eeprom(n);
}

void read_buffer(uint8_t n) {
    read_eeprom(n);
    uint8_t x = 0;
    for (uint8_t i = 0; i < 74; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            if (j == 0) {
                page[n][i].red   = pagebuffer[x];
            } else if (j == 1) {
                page[n][i].green = pagebuffer[x];
            } else {
                page[n][i].blue  = pagebuffer[x];
            }
            //Serial.println(x);
            x++;
        }
    }
    NeoPixels_Write_All(n);
}

void write_eeprom(uint8_t n) {
    EEPROM.begin(1110);
    EEPROM.put(222*n, pagebuffer);
    EEPROM.commit();
    EEPROM.end();
}

void read_eeprom(uint8_t n) {
    EEPROM.begin(1110);
    EEPROM.get(222*n, pagebuffer);
    EEPROM.end();
}

void animation_1_1() {
  NeoPixels_Write_All(0);
}

void animation_1_2() {
  NeoPixels_Write_All(1);
}

void animation_1_3() {
  NeoPixels_Write_All(2);
}

void animation_1_4() {
  NeoPixels_Write_All(3);
}

void animation_1_5() {
  NeoPixels_Write_All(4);
}

// RC Stuff

void RC_Controll() {
    steering_pwm_value = pulseIn(Steering_PWM_PIN, HIGH, 20000);
    speed_pwm_value = pulseIn(Speed_PWM_PIN, HIGH, 20000);
    Serial.print(steering_pwm_value);
    Serial.print(" : ");
    Serial.print(speed_pwm_value);
    if (steering_pwm_value < 100) {
        steering_pwm_value = Steering_PWM_Min + ((Steering_PWM_Max - Steering_PWM_Min) / 2);
    }
    if (speed_pwm_value < 100) {
        speed_pwm_value = Speed_PWM_Min + ((Speed_PWM_Max - Speed_PWM_Min) / 2);
    }
    Serial.print(" : ");
    Serial.print(steering_pwm_value);
    Serial.print(" : ");
    Serial.print(speed_pwm_value);

    int Speed = map(speed_pwm_value, Speed_PWM_Min, Speed_PWM_Max, -255, 255);
    int Steering = map(steering_pwm_value, Steering_PWM_Min, Steering_PWM_Max, -255, 255);

    if (Speed <= 10 && Speed >= -10) {
        Speed = 0;
    }
    if (Steering <= 10 && Steering >= -10) {
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

    if (SpeedA >= 0) {
        digitalWrite(DA, HIGH);
    } else {
        digitalWrite(DA, LOW);
        SpeedA = SpeedA * -1;
    }
    if (SpeedB >= 0) {
        digitalWrite(DB, HIGH);
    } else {
        digitalWrite(DB, LOW);
        SpeedB = SpeedB * -1;
    }

    if (MotorKickstartA == 0 && SpeedA >= KickStartThreshold && MotorKickStartService == 1) {
        analogWrite(PWMA, KickStartLevel);
        KickAStartMillis = millis();
        Serial.println("KickA");
        MotorKickstartA = 1;
    }
    if (MotorKickstartB == 0 && SpeedB >= KickStartThreshold && MotorKickStartService == 1) {
        analogWrite(PWMB, KickStartLevel);
        KickBStartMillis = millis();
        Serial.println("KickB");
        MotorKickstartB = 1;
    }

    if (millis() - KickAStartMillis > KickStartTime) {
        analogWrite(PWMA, SpeedA);
    }
    if (millis() - KickBStartMillis > KickStartTime) {
        analogWrite(PWMB, SpeedB);
    }

    if (MotorKickstartA == 1 && SpeedA <= BottomKickStartThreshold) {
        MotorKickstartA = 0;
    }
    if (MotorKickstartB == 1 && SpeedB <= BottomKickStartThreshold) {
        MotorKickstartB = 0;
    }
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pixels.begin();
    /*pinMode(Steering_PWM_PIN, INPUT);
    pinMode(Speed_PWM_PIN, INPUT);
    pinMode(RobotDispenser_PWM_PIN, INPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(DA, OUTPUT);
    pinMode(DB, OUTPUT);
    LinearActor.attach(D5, 500, 2400);
    Arm.attach(D8, 1200, 2400);*/

    read_buffer(4);
    read_buffer(3);
    read_buffer(2);
    read_buffer(1);
    read_buffer(0);

    update_html_string();

    init_web_server();
    run_at_init();
    run_function_in_millisec(animation_1_1,  500);
    run_function_in_millisec(animation_1_2, 1000);
    run_function_in_millisec(animation_1_3, 1500);
    run_function_in_millisec(animation_1_4, 2000);
    run_function_in_millisec(animation_1_5, 2500);

    //update_html_string();
}

void loop() {
    /*RC_Controll();
    Serial.println(analogRead(A0));
    int DispenserPWM = pulseIn(RobotDispenser_PWM_PIN, HIGH, 20000);
    if (DispenserPWM < 100) {
        DispenserPWM = Trigger_PWM_Min + ((Trigger_PWM_Max - Trigger_PWM_Min) / 2);
    }
    if (DispenserPWM > 1600 && TriggerPressed == 0 && analogRead(A0) <= 200) {
        TriggerPressed = 1;
        if (DispenseProcess == 0 && millis() - DispenseProcessStartMillis > DispenserCooldown) {
            DispenseProcessStartMillis = millis();
            DispenseProcess = 1;
            i = 0;
        }
        if (ArmUp == 1) {
            i = 3;
        }
    } else {
        if (DispenserPWM < 1200 && TriggerPressed == 1) {
            TriggerPressed = 0;
        }
    }

    if (DispenseProcess == 1) {
        if (i == 0) {
            LinearActor.write(178);
            i++;
        }
        if (millis() - DispenseProcessStartMillis >= 2000 && i == 1) {
            LinearActor.write(26);
            i++;
        }
        if (millis() - DispenseProcessStartMillis >= 4000 && i == 2) {
            Arm.write(165);
            ArmUp = 1;
        }
        if (millis() - DispenseProcessStartMillis >= 6000 && i == 3) {
            Arm.write(18);
            ArmUp = 0;
            i++;
        }
        if (i == 4) {
            DispenseProcess = 0;
        }
    }
    */


    server.handleClient();
    run_at_loop();
}
