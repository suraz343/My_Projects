#include <Servo.h>

// Define the pin for the LDR sensor
const int ldrPin = A0;

// Define the pin for the servo motor
const int servoPin = 9;
const int ledPin = 8;

// Define the threshold value for the LDR sensor
const int ldrThreshold = 80;

// Define the angle values for the servo motor
const int closedAngle = 0;
const int openAngle = 180;
const int stepSize = 1; // the angle to move the servo each time

// Define the angle at which to stop the servo motor
const int stopAngle = 90;

// Create a Servo object to control the servo motor
Servo servo;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  // Attach the servo to the servo pin
  servo.attach(servoPin);

  // Set the initial angle of the servo motor to closed
  servo.write(closedAngle);
}

void loop() {
  // Read the value of the LDR sensor
  int ldrValue = analogRead(ldrPin);

  // Print the value of the LDR sensor
  Serial.print("LDR value: ");
  Serial.println(ldrValue);

  // Open the curtains if it's dark (i.e. LDR value is above the threshold)
  if (ldrValue > ldrThreshold) {
    // Move the servo motor to the open angle
    for (int i = closedAngle; i <= openAngle; i += stepSize) {
      servo.write(i);
      digitalWrite(ledPin, LOW);
      delay(15); // adjust this value to change the speed of the servo motor
      if (i == stopAngle) {
        // Stop the servo motor when it reaches the stop angle
        servo.detach();
      }
    }
    Serial.println("Opening curtains");
    delay(1000); // adjust this value to change how long the curtains stay open

    // Re-attach the servo to the servo pin
    servo.attach(servoPin);
    // Move the servo motor to the stop angle
    servo.write(stopAngle);
  } else {
    // Close the curtains if it's light (i.e. LDR value is below the threshold)
    // Move the servo motor to the closed angle
    for (int i = openAngle; i >= closedAngle; i -= stepSize) {
      servo.write(i);
      digitalWrite(ledPin, HIGH);
      delay(15); // adjust this value to change the speed of the servo motor
      if (i == stopAngle) {
        // Stop the servo motor when it reaches the stop angle
        servo.detach();
      }
    }
    Serial.println("Closing curtains");
    delay(1000); // adjust this value to change how long the curtains stay closed

    // Re-attach the servo to the servo pin
    servo.attach(servoPin);
    // Move the servo motor to the stop angle
    servo.write(stopAngle);
  }

  // Wait for a short period of time before checking the LDR sensor again
  delay(500);
}
