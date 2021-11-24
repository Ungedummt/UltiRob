#include <Servo.h>

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


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Steering_PWM_PIN, INPUT);
pinMode(Speed_PWM_PIN, INPUT);
pinMode(RobotDispenser_PWM_PIN, INPUT);
pinMode(PWMA, OUTPUT);
pinMode(PWMB, OUTPUT);
pinMode(DA, OUTPUT);
pinMode(DB, OUTPUT);
LinearActor.attach(D5, 500, 2400);
Arm.attach(D8, 1200, 2400);
}

void loop() {
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
      LinearActor.write(178);
      i++;
    }
    if(millis() - DispenseProcessStartMillis >= 2000 && i == 1){
      LinearActor.write(26);
       i++;
    }
    if(millis() - DispenseProcessStartMillis >= 4000 && i == 2){
      Arm.write(165);
      ArmUp = 1;
    }
    if(millis() - DispenseProcessStartMillis >= 6000 && i == 3){
      Arm.write(18);
      ArmUp = 0;
      i++;
    }
    if(i == 4){
      DispenseProcess = 0;
    }
}

}


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
