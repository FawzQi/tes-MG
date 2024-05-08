#include "MG90.h"

extern Servo mata;
TaskHandle_t MG_task = NULL;
int mginfo[4];

int motion_mg[11][2] = {{0, 1000},
                        {90, 1000},
                        {0, 1000},
                        {180, 2000},
                        {0, 1000},
                        {180, 1000},
                        {90, 1000},
                        {180, 1000},
                        {0, 2000},
                        {180, 1000},
                        {0, 1000}};
void TASK::PlayMotion() {
    xTaskCreate([](void* pvParameters) {
        for (int j = 1; j < 11; j++) {
            int currentAngle = motion_mg[j - 1][0];
            int direction = motion_mg[j][0] > currentAngle ? 1 : -1;
            int interval = motion_mg[j][1] / abs(motion_mg[j][0] - currentAngle);
            for (int i = currentAngle; i != motion_mg[j][0]; i += direction) {
                mata.write(i);
                vTaskDelay(interval * portTICK_PERIOD_MS);
            }
        }
        vTaskDelete(MG_task);
    },
                "MG90", 2000, NULL, 1, &MG_task);
}

void TASK::PlayLeftRigth(int angle1, int angle2, int duration) {
    mginfo[0] = angle1;
    mginfo[1] = angle2;
    mginfo[2] = angle2 > angle1 ? 1 : -1;
    mginfo[3] == duration / abs(angle1 - angle2);

    if (MG_task != NULL && eTaskGetState(MG_task) == eTaskState::eBlocked) {
        vTaskDelete(MG_task);
    }

    xTaskCreate([](void* pvParameters) {
        for (int i = mginfo[0]; i != mginfo[1]; i += mginfo[2]) {
            mata.write(i);
            vTaskDelay(24 * portTICK_PERIOD_MS);
        }
        for (int i = mginfo[1]; i != mginfo[0]; i -= mginfo[2]) {
            mata.write(i);
            vTaskDelay(24 * portTICK_PERIOD_MS);
        }
    },
                "MG90", 2000, NULL, 1, &MG_task);
}

void PlayAngle(int angle, int duration) {
    if (angle < 0) {
        angle = 0;
    } else if (angle > 180) {
        angle = 180;
    }
    int direction = angle > mata.read() ? 1 : -1;
    int lastMove = millis();
    float interval = duration / abs(angle - mata.read());
    for (int i = mata.read(); i != angle;) {
        mata.write(i);
        if (millis() - lastMove > interval) {
            i += direction;
            lastMove = millis();
        }
    }
}

void PlayWave(int angle1, int angle2, int duration) {
    if (angle1 < 0) {
        angle1 = 0;
    } else if (angle1 > 180) {
        angle1 = 180;
    }
    if (angle2 < 0) {
        angle2 = 0;
    } else if (angle2 > 180) {
        angle2 = 180;
    }
    int direction = angle2 > angle1 ? 1 : -1;
    int lastMove = millis();
    float interval = duration / abs(angle1 - angle2);
    if (direction > 0) {
        for (int i = angle1; i != angle2;) {
            mata.write(i);
            if (millis() - lastMove > interval) {
                i += direction;
                lastMove = millis();
                if (i == angle2) {
                    direction = -direction;
                }
            }
        }
    } else {
        for (int i = angle2; i != angle1;) {
            mata.write(i);
            if (millis() - lastMove > interval) {
                i += direction;
                lastMove = millis();
                if (i == angle1) {
                    direction = -direction;
                }
            }
        }
    }
}

// MG90::MG90() {
//     xTaskCreate(Task, "MG90", 10000, this, 1, NULL);
// }

// void MG90::Task(void* pvParameters) {
//     MG90info* info = (MG90info*)pvParameters;
//     for (int i = info->currentAngle; i != info->angle; i += info->direction) {
//         this->write(i);
//         vTaskDelay(info->interval);
//     }
//     info->MGdone = true;
//     delete info;
//     vTaskDelete(NULL);
// }