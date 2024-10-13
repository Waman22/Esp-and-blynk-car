#define BLYNK_TEMPLATE_ID "TMPL2hfGsMRs5"  // Unique ID for the Blynk template
#define BLYNK_TEMPLATE_NAME "LED ON AND OFF" // Name of the Blynk template

#define BLYNK_PRINT Serial                   // Enable serial output for Blynk
#include <WiFi.h>                           // Include WiFi library
#include <WiFiClient.h>                     // Include WiFi client library
#include <BlynkSimpleEsp32.h>               // Include Blynk library for ESP32

// Motor A pins
int motor1Pin1 = 27;                       // Control pin 1 for Motor A
int motor1Pin2 = 26;                       // Control pin 2 for Motor A
int enable1Pin = 14;                       // PWM enable pin for Motor A

// Motor B pins
int motor2Pin1 = 25;                       // Control pin 1 for Motor B
int motor2Pin2 = 33;                       // Control pin 2 for Motor B
int enable2Pin = 12;                       // PWM enable pin for Motor B

// Setting PWM properties
const int freq = 30000;                    // PWM frequency
const int pwmChannel = 0;                  // PWM channel for Motor A
const int resolution = 8;                  // PWM resolution
int dutyCycle = 255;                       // Initial duty cycle value

// Flags for Blynk buttons
bool one = 1;                              // Flag for forward movement
bool two = 1;                              // Flag for reverse movement
bool three = 1;                            // Flag for left turn
bool four = 1;                             // Flag for right turn
bool five = 1;                             // Flag for room detection

#define PIR_PIN 15                         // Define the pin for the PIR sensor
const int MOTION_THRESHOLD = 1830;        // Define the motion threshold value for the PIR sensor

// Ultrasonic sensor pins
int EchoPin = 4;                           // Assign echo pin for ultrasonic sensor
int TriggPin = 15;                         // Assign trigger pin for ultrasonic sensor

// Enter your Auth token for Blynk
char auth[] = "1pl3jXduGrt2Aw6O7oIVX9_LazXqePCo";

// Enter your WiFi SSID and password
char ssid[] = "Huawei Y7";                 // WiFi SSID
char pass[] = "tyr567hi";                  // WiFi password

// Function to control the motor based on Blynk button V1
BLYNK_WRITE(V1) {
    one = param.asInt();                   // Read the state of button V1
    if(one == 1) {                         // If button is pressed
        moveForward();                     // Move the motor forward
        Serial.println("Moving Forward");
    } else {
        STOP();                            // Stop the motors
        Serial.println("Stopped");
    }
}

// Function to control the motor based on Blynk button V2
BLYNK_WRITE(V2) {
    two = param.asInt();                   // Read the state of button V2
    if(two == 1) {                         // If button is pressed
        moveReverse();                     // Move the motor in reverse
        Serial.println("Moving Backwards");
    } else {
        STOP();                            // Stop the motors
        Serial.println("Stopped");
    }
}

// Function to control the motor based on Blynk button V3
BLYNK_WRITE(V3) {
    three = param.asInt();                 // Read the state of button V3
    if(three == 1) {                       // If button is pressed
        moveLeft();                        // Move the motor to the left
        Serial.println("Turning Left");
    } else {
        STOP();                            // Stop the motors
        Serial.println("Stopped");
    }
}

// Function to control the motor based on Blynk button V4
BLYNK_WRITE(V4) {
    four = param.asInt();                  // Read the state of button V4
    if(four == 1) {                        // If button is pressed
        moveRight();                       // Move the motor to the right
        Serial.println("Turning Right");
    } else {
        STOP();                            // Stop the motors
        Serial.println("Stopped");
    }
}

// Function to control the room behavior based on Blynk button V5
BLYNK_WRITE(V5) {
    five = param.asInt();                  // Read the state of button V5
    if(five == 1) {                        // If button is pressed
        Room();                            // Execute room function
        Serial.println("Room on");
    } else {
        STOP();                            // Stop the motors
        Serial.println("Stopped");
    }
}

void setup() {
    // Set motor control pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);

    // Set Motor B control pins as outputs
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);

    pinMode(PIR_PIN, INPUT);                // Set PIR sensor pin as input

    pinMode(TriggPin, OUTPUT);              // Set trigger pin for ultrasonic sensor as output
    pinMode(EchoPin, INPUT);                // Set echo pin for ultrasonic sensor as input
    Serial.begin(115200);                   // Start serial communication
    delay(100);
  
    // Configure LEDC PWM for motors
    ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);
    ledcAttachChannel(enable2Pin, freq, resolution, pwmChannel);
    
    // Print test message
    Serial.print("Testing DC Motor...");
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); // Connect to Blynk server
}

void loop() {
    // Main loop
    Blynk.run();                             // Process Blynk commands
}

void moveForward() {
    // Move DC motor forward
    digitalWrite(motor1Pin1, LOW);         // Set Motor A direction
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, LOW);         // Set Motor B direction
    digitalWrite(motor2Pin2, HIGH);
    
    // Increase speed using PWM
    while (dutyCycle <= 255) {
        ledcWrite(enable1Pin, dutyCycle);   // Set PWM duty cycle for Motor A
        Serial.print("Forward with duty cycle: ");
        Serial.println(dutyCycle);
        dutyCycle += 5;                     // Increase duty cycle
        delay(500);                         // Wait for half a second
    }
    dutyCycle = 255;                        // Reset duty cycle to maximum
}

void moveReverse() {
    // Move DC motor backwards
    Serial.println("Moving Backwards");
    digitalWrite(motor1Pin1, HIGH);       // Set Motor A direction
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, HIGH);       // Set Motor B direction
    digitalWrite(motor2Pin2, LOW); 
}

void moveLeft() {
    // Turn left
    digitalWrite(motor1Pin1, LOW);        // Set Motor A direction
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, HIGH);       // Set Motor B direction
    digitalWrite(motor2Pin2, LOW); 
}

void moveRight() {
    // Turn right
    digitalWrite(motor1Pin1, HIGH);       // Set Motor A direction
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);        // Set Motor B direction
    digitalWrite(motor2Pin2, HIGH); 
}

void STOP() {
    // Stop the DC motor
    Serial.println("Motor stopped");
    digitalWrite(motor1Pin1, LOW);        // Stop Motor A
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);        // Stop Motor B
    digitalWrite(motor2Pin2, LOW); 
}

void Room() {
    // Measure distance using the ultrasonic sensor
    digitalWrite(TriggPin, HIGH);          // Trigger the ultrasonic sensor
    delayMicroseconds(10);                  // Wait for 10 microseconds
    digitalWrite(TriggPin, LOW);           // Turn off the trigger

    int duration = pulseIn(EchoPin, HIGH); // Read the echo duration
    int distance = duration * 0.034 / 2;   // Calculate distance in cm

    Serial.print("Water Level (cm): ");    
    Serial.println(distance);               // Print distance in cm

    Blynk.virtualWrite(V5, distance);      // Send distance to Blynk

    // If the distance is less than 30 cm, perform actions
    if(distance < 30) {
        moveReverse();                      // Move backward
        delay(2000);                       // Wait for 2 seconds
        moveLeft();                        // Turn left
        delay(1000);                       // Wait for 1 second
        moveForward();                     // Move forward
        delay(2000);                       // Wait for 2 seconds
        moveRight();                       // Turn right
        delay(1000);                       // Wait for 1 second
    } else {
        moveForward();                     // If no obstruction, keep moving forward
    }
}
