#include <Arduino.h>
#include <ESP32Servo.h>
#include <MG90.h>
// #include <Servo.h>

#define buttonpin 13
bool released = true;
bool wave = 0;
int t = 1;
int mginfo[4];

// MG90 Mata;
// MG90 emge;

Servo mata;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    mata.attach(2);

    // emge.attach(2);

    pinMode(buttonpin, INPUT_PULLUP);

    TASK::PlayMotion();
    // PlayLeftRigth(40, 140, 2000);
    // emge.PlayAngle(180, 3000);
}

void loop() {
    if (millis() < 282000) Serial.println("loop");
    delay(1000);
}
