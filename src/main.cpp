#include <Arduino.h>
#include <ESP32Servo.h>
#include <MG90.h>
// #include <Servo.h>

#define buttonpin 13
bool released = true;
int t = 1;

// MG90 Mata;
Servo mata;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    mata.attach(2);
    mata.write(0);
    pinMode(buttonpin, INPUT_PULLUP);

    // TASK::PlayMotion();
}

void loop() {
    // put your main code here, to run repeatedly:
    PlayAngle(180, 3000);
}
