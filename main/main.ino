/* author- sadman alvee 
 * Owner/Founder @ impedancePlus
 */
#include <Servo.h>

// ULTRASONIC SENSOR PINS
int trigPin = 10;
int echoPin = 9;
long signalTravelTime;
int distance;

// SERVO PINS
int servoPin = 3;

// LED-BUZZER PINS
int greenLedPin = 5;
int redLedPin = 13;
int buzzerPin = 2;

// Create objects of type -Servo
Servo thisServo;

void _configureSignalSystem() {
  //40 cms
  if (distance <= 40) {

    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(20);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(20);
  }
  else if (distance > 40) {
    digitalWrite(greenLedPin, HIGH);
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int _configureUltrasonicSensor() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  signalTravelTime = pulseIn(echoPin, HIGH); //returns the sound wave travel time in microseconds
  distance = signalTravelTime * 0.034 / 2; // in centimeters
  return distance;
}

void _configureArduinoAndProcessingIDE(int j, int distanceFinal) {
  Serial.print(j); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distanceFinal); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
}

void _configureServoMotor() {
  for (int i = 15; i <= 165; i++) {
    thisServo.write(i);
    delay(10);
    distance = _configureUltrasonicSensor();
    _configureArduinoAndProcessingIDE(i, distance);
    _configureSignalSystem();
  }
  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 165; i >= 15; i--) {
    thisServo.write(i);
    delay(10);
    distance = _configureUltrasonicSensor();
    _configureArduinoAndProcessingIDE(i, distance);
    _configureSignalSystem();
  }
}

void setup() {
  // put your setup code here, to run once:

  //Set-up Ultrasonic Sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  //Set-up Servo pins
  thisServo.attach(servoPin); // Defines on which pin is the servo motor attached
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // rotates the servo motor from 15 to 165 degrees
  _configureServoMotor();
}
