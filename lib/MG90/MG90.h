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
}  // namespace TASK

void PlayLeftRigth(int angle1, int angle2, int duration);
void PlayAngle(int angle, int duration);
void PlayWave(int angle1, int angle2, int duration);

enum MG {
    PLAY_ANGLE,
    PLAY_WAVE
};

class MG90 : public Servo {
   private:
    uint8_t target1;
    uint8_t target2;
    uint8_t mode;
    int duration;
    bool isDone = true;

   public:
    void PlayAngle(int angle, int duration);
    void PlayWave(int angle1, int angle2, int duration);
    void loop();
    void MoveWithoutDelay(int minAngle, int maxAngle, int speed);
};

#endif  // MG90_H
        /*
         */