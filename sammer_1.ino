\// Created by Utkarsh Kumar 
// On date 27 - 11 - 2023 
// Youtube channel link :-https://www.youtube.com/@techutkarsh1744
#include "mp3tf16p.h"

#define trigPin1 3 // Ultrasonic sensor 1 trigger pin
#define echoPin1 4 // Ultrasonic sensor 1 echo pin
#define maxDistance1 500 // Maximum distance for ultrasonic sensor 1
#define trigPin2 10 // Ultrasonic sensor 2 trigger pin
#define echoPin2 11 // Ultrasonic sensor 2 echo pin
#define maxDistance2 500 // Maximum distance for ultrasonic sensor 2

MP3Player mp3(7, 8);

int moistureSensorPin = A0; // Moisture sensor pin (changed to analog pin)
int irSensorPin = 12; // IR sensor pin
int vibratorMotorPin = 9; // Vibrator motor pin

void setup() {
    // Setup ultrasonic sensors
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    
    // Setup other sensors and actuators
    pinMode(moistureSensorPin, INPUT); // Set moisture sensor pin as input
    pinMode(irSensorPin, INPUT); // Set IR sensor pin as input
    pinMode(vibratorMotorPin, OUTPUT); // Set vibrator motor pin as output
    
    // Initialize MP3 player
    mp3.initialize();
    mp3.player.volume(30);
    delay(1000);
    mp3.playTrackNumber(3, 25);

    // Initialize serial communication
    Serial.begin(9600);
}

void loop() {
    // Ultrasonic Sensor 1
    long duration1, distance1;
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1 / 2) * 0.0343;

    if (distance1 <= 20) { // If distance is less than 50 cm
        digitalWrite(vibratorMotorPin, HIGH); // Turn on vibrator motor
        mp3.playTrackNumber(4, 25);
        delay(500); // Vibrate for 500 milliseconds
        digitalWrite(vibratorMotorPin, LOW); // Turn off vibrator motor
    }

    // Ultrasonic Sensor 2
    long duration2, distance2;
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2 / 2) * 0.0343;

    if (distance2 <= 20) { // If distance is less than 50 cm
        digitalWrite(vibratorMotorPin, HIGH); // Turn on vibrator motor
        mp3.playTrackNumber(5, 25);
        delay(500); // Vibrate for 500 milliseconds
        digitalWrite(vibratorMotorPin, LOW); // Turn off vibrator motor
    }

    // Print distances to serial monitor
    Serial.print("Distance from Sensor 1: ");
    Serial.print(distance1);
    Serial.println(" cm");
    Serial.print("Distance from Sensor 2: ");
    Serial.print(distance2);
    Serial.println(" cm");

    delay(1000); // Adjust as needed

    // Check moisture sensor
    int moistureSensorValue = analogRead(moistureSensorPin);

    if (moistureSensorValue < 500) { // Adjust threshold as needed
        digitalWrite(vibratorMotorPin, HIGH); // Turn on vibrator motor
        mp3.playTrackNumber(1, 25);
        delay(500); // Vibrate for 500 milliseconds
        digitalWrite(vibratorMotorPin, LOW); // Turn off vibrator motor
    }

    // Check IR sensor
    int irSensorValue = digitalRead(irSensorPin);

    if (irSensorValue == LOW) { // If IR sensor detects an object
        digitalWrite(vibratorMotorPin, HIGH); // Turn on vibrator motor
        mp3.playTrackNumber(2, 25);
        delay(500); // Vibrate for 500 milliseconds
        digitalWrite(vibratorMotorPin, LOW); // Turn off vibrator motor
    }
}
