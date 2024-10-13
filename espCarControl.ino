#define BLYNK_TEMPLATE_ID "TMPL2DPE4CuGq"
#define BLYNK_TEMPLATE_NAME "4wd"
#define BLYNK_AUTH_TOKEN 

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

//motor b
int motor2Pin1 = 25; 
int motor2Pin2 = 33; 
int enable2Pin = 12; 


// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;


bool one=0;
bool two=0;
bool three = 0;
bool four = 0;

// Enter your Auth token
char auth[] = "WjBdqA8gRyME-oE9dAHiYfD9N5b2O52a";

//Enter your WIFI SSID and password
char ssid[] = "Huawei Y7";
char pass[] = "tyr567hi";


BLYNK_WRITE(V1){
one = param.asInt();
 if(one ==1)
 {
  moveForward();
  Serial.println("Moving Foward");
 }
 else{
    STOP();
    Serial.println("Stopped");
 }
}

BLYNK_WRITE(V2){
 two = param.asInt();
 if(two ==0)
 {
  moveReverse();
  Serial.println("outlet on");
 }
 else{
  STOP();
    Serial.println("Stopped");
 }
}

BLYNK_WRITE(V3){
 three = param.asInt();
 if(three ==0)
 {
  moveLeft();
  Serial.println("outlet on");
 }
 else{

    STOP();
    Serial.println("Stopped");
 }
}

BLYNK_WRITE(V4){
 four = param.asInt();
 if(four ==0)
 {
  moveRight();
  Serial.println("outlet on");
 }
 else{
    
    STOP();
    Serial.println("Stopped");
 }
}

void setup() {
 // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  //MotorB
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LEDC PWM
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);

  ledcAttachChannel(enable2Pin, freq, resolution, pwmChannel);
  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
}


void moveForward() {
 // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  while (dutyCycle <= 255){
    ledcWrite(enable1Pin, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
}

void moveReverse() {
  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
}

void moveLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin1, LOW);

}

void moveRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin1, HIGH);

}

void STOP(){
    // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}