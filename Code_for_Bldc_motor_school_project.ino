#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX pins of HC-05

// Motor control pins
const int motorPWM = 9;   // PWM pin for motor speed control
const int motorDir1 = 7;  // Direction pin 1
const int motorDir2 = 8;  // Direction pin 2

void setup() {
  // Initialize Serial communication with a baud rate of 9600
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Set motor control pins as output
  pinMode(motorPWM, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();

    // Check the received command from Bluetooth
    switch (command) {
      case 'F':  // Forward
        moveForward();
        break;
      case 'B':  // Backward
        moveBackward();
        break;
      case 'S':  // Stop
        stopMotor();
        break;
      case '1':  // Increase speed
        increaseSpeed();
        break;
      case '2':  // Decrease speed
        decreaseSpeed();
        break;
    }
  }
}

// Move the motor forward
void moveForward() {
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
}

// Move the motor backward
void moveBackward() {
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, HIGH);
}

// Stop the motor
void stopMotor() {
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);
}

// Increase motor speed
void increaseSpeed() {
  int currentSpeed = analogRead(motorPWM);
  if (currentSpeed < 255) {
    analogWrite(motorPWM, currentSpeed + 10);
  }
}

// Decrease motor speed
void decreaseSpeed() {
  int currentSpeed = analogRead(motorPWM);
  if (currentSpeed > 0) {
    analogWrite(motorPWM, currentSpeed - 10);
  }
}
