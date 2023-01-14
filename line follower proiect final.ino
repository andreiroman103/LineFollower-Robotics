#include <QTRSensors.h>

const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

int m1Speed = 0;
int m2Speed = 0;

float kp = 20; 
float ki = 0;
float kd = 5; 

float p = 1;
float i = 0;
float d = 0;

float error = 0;
float lastError = 0;
const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 240; 


QTRSensors qtr;

const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = {0, 0, 0, 0, 0, 0};

bool aligned = false;
long long calibrationTime = 6000;
int lastErrorValue = 0;

void setup() {
  // pinMode setup
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  m1Speed = 180;
  m2Speed = -180;
}

void loop() {
  // auto calibration

  if (millis() < calibrationTime) {
    calibrateLineFollower();    
  }
  else if (!aligned)
    alignLine();
  else {
    int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -75, 75);
    p = error;
    i = i + error;
    d = error - lastError;
    int motorSpeed = kp * p + ki * i + kd * d; 
    m1Speed = baseSpeed;
    m2Speed = baseSpeed;
    
    if (error < 0) {
      m1Speed += motorSpeed;
    }
    else if (error > 0) {
      m2Speed -= motorSpeed;
    }
    m1Speed = constrain(m1Speed, -255, maxSpeed);
    m2Speed = constrain(m2Speed, -255, maxSpeed);
    setMotorSpeed(m1Speed, m2Speed);
  }
}

void alignLine(){
  // function to center the line follower in order to start as smoothly as possible
  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -75, 75);
  if (error < 0)    
    setMotorSpeed(-200, 200);
  else if (error > 0)    
    setMotorSpeed(200, -200);
  else {
    setMotorSpeed(0, 0);
    aligned = true;      
  }
}
  
void calibrateLineFollower(){
  qtr.calibrate();
  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -75, 75);

  if (error == 75 || error == -75) {  // if we are out of the line completely, change the direction of the steering   
    if (lastErrorValue != error)
      {
        m1Speed = -m1Speed;
        m2Speed = -m2Speed;
      }    
    }
  lastErrorValue = error;
  setMotorSpeed(m1Speed, m2Speed);
}
  
// each arguments takes values between -255 and 255. The negative valuesrepresent the motor speed in reverse.
void setMotorSpeed(int motor1Speed, int motor2Speed) {
  if (motor1Speed == 0) {
  digitalWrite(m11Pin, LOW);
  digitalWrite(m12Pin, LOW);
  analogWrite(m1Enable, motor1Speed);
  }
  else {
  if (motor1Speed > 0) {
  digitalWrite(m11Pin, HIGH);
  digitalWrite(m12Pin, LOW);
  analogWrite(m1Enable, motor1Speed);
  }
  if (motor1Speed < 0) {
  digitalWrite(m11Pin, LOW);
  digitalWrite(m12Pin, HIGH);
  analogWrite(m1Enable, -motor1Speed);
  }
  }
  if (motor2Speed == 0) {
  digitalWrite(m21Pin, LOW);
  digitalWrite(m22Pin, LOW);
  analogWrite(m2Enable, motor2Speed);
  }
  else {
  if (motor2Speed > 0) {
  digitalWrite(m21Pin, HIGH);
  digitalWrite(m22Pin, LOW);
  analogWrite(m2Enable, motor2Speed);
  }
  if (motor2Speed < 0) {
  digitalWrite(m21Pin, LOW);
  digitalWrite(m22Pin, HIGH);
  analogWrite(m2Enable, -motor2Speed);
  }
  }
}