The espcarcontrol is a  project that involves 
Esp32 and blynk Iot 
This project controls a 4wd vehicle with l298N motor driver 
To make car move correctly swapped in3 and in4 on the breadbod it self


#define BLYNK_TEMPLATE_ID "TMPL2DPE4CuGq" 
#define BLYNK_TEMPLATE_NAME "4wd"
#define BLYNK_AUTH_TOKEN // Token should be filled in

#define BLYNK_PRINT Serial  // Enabling serial printing for debugging
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN: These are used to connect the ESP32 to a specific Blynk project.
BLYNK_PRINT Serial: This allows serial output for debugging.
The libraries included here (WiFi.h, WiFiClient.h, BlynkSimpleEsp32.h) are for enabling Wi-Fi and connecting to the Blynk app.

// Motor A Pins
int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;

// Motor B Pins
int motor2Pin1 = 25;
int motor2Pin2 = 33;
int enable2Pin = 12;
These variables define the pins on the ESP32 connected to the motor driver.

// PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 255;
These define PWM settings for motor speed control.

bool one=1, two=1, three=1, four=1;
These are boolean flags that will be used to control the motors remotely through Blynk (forward, reverse, left, right).


char auth[] = "WjBdqA8gRyME-oE9dAHiYfD9N5b2O52a";  // Blynk Auth Token
char ssid[] = "Huawei Y7";  // Wi-Fi SSID
char pass[] = "tyr567hi";  // Wi-Fi Password
auth[]: Blynk Auth Token to authenticate the ESP32 with the Blynk app.
ssid[] and pass[]: Wi-Fi credentials to connect the ESP32 to the internet.
Blynk Write Functions
These functions are called when buttons or sliders in the Blynk app are used. They control the movement of the motor.


BLYNK_WRITE(V1) {
  one = param.asInt();
  if (one == 1) {
    moveForward();
    Serial.println("Moving Forward");
  } else {
    STOP();
    Serial.println("Stopped");
  }
}
V1: Button in the Blynk app for moving the vehicle forward. It calls the moveForward() function if the button is pressed (one == 1), otherwise it stops the motor.

BLYNK_WRITE(V2) {
  two = param.asInt();
  if (two == 1) {
    moveReverse();
    Serial.println("Moving Reverse");
  } else {
    STOP();
    Serial.println("Stopped");
  }
}
V2: Button in the Blynk app for moving the vehicle in reverse.

BLYNK_WRITE(V3) {
  three = param.asInt();
  if (three == 1) {
    moveLeft();
    Serial.println("Moving Left");
  } else {
    STOP();
    Serial.println("Stopped");
  }
}
V3: Button in the Blynk app for moving the vehicle left.

BLYNK_WRITE(V4) {
  four = param.asInt();
  if (four == 1) {
    moveRight();
    Serial.println("Moving Right");
  } else {
    STOP();
    Serial.println("Stopped");
  }
}
V4: Button in the Blynk app for moving the vehicle right.
Setup Function

void setup() {
  // Set motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // Configure PWM channels
  ledcAttachChannel(enable1Pin, pwmChannel, freq, resolution);
  ledcAttachChannel(enable2Pin, pwmChannel, freq, resolution);
  
  Serial.begin(115200);  // Initialize serial for debugging

  // Blynk initialization
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}
Initializes motor pins as outputs, configures PWM channels for motor speed control, and connects to Blynk using the Wi-Fi credentials and authentication token.
Main Loop

void loop() {
  Blynk.run();  // Blynk event loop
}
This keeps the Blynk communication active, allowing the app to control the motors.
Motor Control Functions
These functions handle the motor movements.


void moveForward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  while (dutyCycle <= 255) {
    ledcWrite(enable1Pin, dutyCycle);
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 255;
}
Moves the motors forward by setting the appropriate motor driver pins.

void moveReverse() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
}
Moves the motors backward.

void moveLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin1, LOW);
}
Turns the motors to the left.

void moveRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin1, HIGH);
}
Turns the motors to the right.

void STOP() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  Serial.println("Motor stopped");
}
Stops the motors.
Steps to Run the Code:
Set up Blynk:

Download the Blynk app from the Google Play Store or Apple App Store.
Create a new project in Blynk, select ESP32 as the device.
Copy the Auth Token provided for your project.
Install Libraries in Arduino IDE:

Install the Blynk library in Arduino IDE via Sketch > Include Library > Manage Libraries... search for Blynk and install it.
Install the ESP32 board by going to Tools > Board > Board Manager, search for ESP32 and install it.
Set up Wi-Fi and Blynk:

Replace the Auth Token, Wi-Fi SSID, and Wi-Fi Password in the code with your values.
Upload the Code to ESP32:

Connect your ESP32 to the computer.
Select ESP32 Dev Module from Tools > Board.
Select the correct port under Tools > Port.
Click Upload in Arduino IDE.
Run the Project:

Open the Blynk app on your phone.
Add buttons for V1, V2, V3, and V4 for controlling forward, reverse, left, and right movements.
Press the buttons to control the motors remotely.
Important Notes:
Make sure you have a motor driver like L298N or L293D to interface with the motors.
Ensure that the motor driver and ESP32 are properly powered.
