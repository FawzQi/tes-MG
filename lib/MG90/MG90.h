#ifndef MG90_H
#define MG90_H
#include <ESP32Servo.h>

typedef struct {
    int angle;
    int direction;
    int duration;
    int interval;
    int currentAngle;
    bool MGdone;
} MG90info;

extern TaskHandle_t MG_task;
namespace TASK {
void PlayMotion();
void PlayLeftRigth(int angle1, int angle2, int duration);
}  // namespace TASK

void PlayAngle(int angle, int duration);
void PlayWave(int angle1, int angle2, int duration);
#endif  // MG90_H