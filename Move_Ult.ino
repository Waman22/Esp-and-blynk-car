// Motor A
int enA = 9; // Enable pin for Motor A
int in1 = 2; // Input pin 1 for Motor A
int in2 = 3; // Input pin 2 for Motor A

// Motor B
int enB = 10; // Enable pin for Motor B
int in3 = 5;  // Input pin 1 for Motor B
int in4 = 4;  // Input pin 2 for Motor B

// Define pins for the ultrasonic sensor
#define PIN_TRIG 7 // Trigger pin
#define PIN_ECHO 8 // Echo pin

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  pinMode(PIN_TRIG, OUTPUT); // Set the trigger pin as OUTPUT
  pinMode(PIN_ECHO, INPUT); // Set the echo pin as INPUT
}

int measureDistance() {
  digitalWrite(PIN_TRIG, HIGH); // Send a HIGH pulse to the trigger
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(PIN_TRIG, LOW); // Set the trigger pin to LOW

  // Read the duration of the echo
  int duration = pulseIn(PIN_ECHO, HIGH); // Measure duration in microseconds
  
  // Convert the duration to distance in centimeters
  return duration / 58; // Distance calculation
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, 255); // Set speed for Motor A
  analogWrite(enB, 255); // Set speed for Motor B
  Serial.println("Moving Forward");
}

void Reverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 255); // Set speed for Motor A
  analogWrite(enB, 255); // Set speed for Motor B
  Serial.println("Reversing");
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); // Stop motor A
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); // Turn motor B forward
  
  analogWrite(enA, 0); // Motor A stopped
  analogWrite(enB, 255); // Motor B full speed
  Serial.println("Turning Left");
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); // Turn motor A forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); // Stop motor B
  
  analogWrite(enA, 255); // Motor A full speed
  analogWrite(enB, 0); // Motor B stopped
  Serial.println("Turning Right");
}

void loop() {
  int distanceCM = measureDistance(); // Measure distance

  Serial.print("Distance in CM: ");
  Serial.println(distanceCM); // Print the calculated distance

  if (distanceCM <= 20) { // If an obstacle is detected within 20 cm
    // Perform obstacle avoidance behavior
    Serial.println("Obstacle detected! Executing avoidance maneuvers.");
    
 

    Reverse(); // Move backward
    delay(1000); // Adjust this delay based on your reversing speed

    turnLeft(); // Turn left
    delay(1000); // Adjust this delay based on your turning speed

    moveForward(); // Move forward
    delay(2000); // Move forward for 2 seconds
  } else {
    moveForward(); // Continue moving forward
    delay(1000); // Move forward for 1 second
  }
}
