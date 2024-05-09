#include "MG90.h"

extern Servo mata;
TaskHandle_t MG_task = NULL;
//                    Angle frame
int motion_mg[142][2] = {
    {0, 0},
    {0, 2000},
    {90, 3000},
    {0, 4500},
    {180, 7500},
    {0, 9000},
    {180, 10500},
    {90, 12000},
    {180, 13500},
    {0, 16500},
    {180, 18000},
    {0, 19500},
    {90, 21000},
    {0, 22500},
    {180, 25500},
    {0, 28500},
    {180, 31500},
    {90, 33000},
    {180, 34500},
    {0, 37500},
    {180, 40500},
    {0, 43500},
    {90, 45000},
    {0, 46500},
    {180, 49500},
    {0, 52500},
    {180, 55500},
    {90, 57000},
    {180, 58500},
    {0, 61500},
    {180, 64500},
    {0, 67500},
    {90, 3000 + 67500},
    {0, 4500 + 67500},
    {180, 7500 + 67500},
    {0, 9000 + 67500},
    {180, 10500 + 67500},
    {90, 12000 + 67500},
    {180, 13500 + 67500},
    {0, 16500 + 67500},
    {180, 18000 + 67500},
    {0, 19500 + 67500},
    {90, 3000 + 87000},
    {0, 4500 + 87000},
    {180, 7500 + 87000},
    {0, 9000 + 87000},
    {180, 10500 + 87000},
    {90, 12000 + 87000},
    {180, 13500 + 87000},
    {0, 16500 + 87000},
    {180, 18000 + 87000},
    {0, 19500 + 87000},
    {90, 3000 + 106500},
    {0, 4500 + 106500},
    {180, 7500 + 106500},
    {0, 9000 + 106500},
    {180, 10500 + 106500},
    {90, 12000 + 106500},
    {180, 13500 + 106500},
    {0, 16500 + 106500},
    {180, 18000 + 106500},
    {0, 19500 + 106500},
    {90, 3000 + 126000},
    {0, 4500 + 126000},
    {180, 7500 + 126000},
    {0, 9000 + 126000},
    {180, 10500 + 126000},
    {90, 12000 + 126000},
    {180, 13500 + 126000},
    {0, 16500 + 126000},
    {180, 18000 + 126000},
    {0, 19500 + 126000},
    {90, 3000 + 145500},
    {0, 4500 + 145500},
    {180, 7500 + 145500},
    {0, 9000 + 145500},
    {180, 10500 + 145500},
    {90, 12000 + 145500},
    {180, 13500 + 145500},
    {0, 16500 + 145500},
    {180, 18000 + 145500},
    {0, 19500 + 145500},
    {90, 3000 + 165000},
    {0, 4500 + 165000},
    {180, 7500 + 165000},
    {0, 9000 + 165000},
    {180, 10500 + 165000},
    {90, 12000 + 165000},
    {180, 13500 + 165000},
    {0, 16500 + 165000},
    {180, 18000 + 165000},
    {0, 19500 + 165000},
    {90, 3000 + 184500},
    {0, 4500 + 184500},
    {180, 7500 + 184500},
    {0, 9000 + 184500},
    {180, 10500 + 184500},
    {90, 12000 + 184500},
    {180, 13500 + 184500},
    {0, 16500 + 184500},
    {180, 18000 + 184500},
    {0, 19500 + 184500},
    {90, 3000 + 204000},
    {0, 4500 + 204000},
    {180, 7500 + 204000},
    {0, 9000 + 204000},
    {180, 10500 + 204000},
    {90, 12000 + 204000},
    {180, 13500 + 204000},
    {0, 16500 + 204000},
    {180, 18000 + 204000},
    {0, 19500 + 204000},
    {90, 3000 + 223500},
    {0, 4500 + 223500},
    {180, 7500 + 223500},
    {0, 9000 + 223500},
    {180, 10500 + 223500},
    {90, 12000 + 223500},
    {180, 13500 + 223500},
    {0, 16500 + 223500},
    {180, 18000 + 223500},
    {0, 19500 + 223500},
    {90, 3000 + 243000},
    {0, 4500 + 243000},
    {180, 7500 + 243000},
    {0, 9000 + 243000},
    {180, 10500 + 243000},
    {90, 12000 + 243000},
    {180, 13500 + 243000},
    {0, 16500 + 243000},
    {180, 18000 + 243000},
    {0, 19500 + 243000},
    {90, 3000 + 262500},
    {0, 4500 + 262500},
    {180, 7500 + 262500},
    {0, 9000 + 262500},
    {180, 10500 + 262500},
    {90, 12000 + 262500},
    {180, 13500 + 262500},
    {0, 16500 + 262500},
    {180, 18000 + 262500},
    {0, 19500 + 262500}
    // angle , millis

};
void TASK2::PlayMotion() {
    Serial.println("Play Motion");
    xTaskCreate([](void* pvParameters) {
        mata.attach(2);
        int currentAngle;
        int direction;
        float interval;
        int totalDelay = 0;
        for (int j = 1; j < int(sizeof(motion_mg) / sizeof(motion_mg[0])); j++) {
            currentAngle = motion_mg[j - 1][0];
            direction = motion_mg[j][0] > currentAngle ? 1 : -1;
            float sisa = 0;
            for (int i = currentAngle; i != motion_mg[j][0]; i += direction) {
                mata.write(i);
                interval = static_cast<float>((motion_mg[j][1] - motion_mg[j - 1][1])) / abs(motion_mg[j][0] - currentAngle);
                sisa += interval - int(interval);
                if (sisa >= 1.00) {
                    sisa -= 1.00;
                    interval += 1.00;
                }
                totalDelay += int(interval);
                vTaskDelay(interval * portTICK_PERIOD_MS);
            }
            mata.write(motion_mg[j][0]);
            vTaskDelay((motion_mg[j][1] - totalDelay) * portTICK_PERIOD_MS);
            totalDelay += motion_mg[j][1] - totalDelay;
        }
        Serial.println("MG MOTION Done");
        Serial.print("Total Delay : ");
        Serial.println(totalDelay);
        Serial.print("Total Millis : ");
        Serial.println(motion_mg[sizeof(motion_mg) / sizeof(motion_mg[0]) - 1][1]);
        Serial.print("Current Millis : ");
        Serial.println(millis());

        vTaskDelete(MG_task);
    },
                "MG90", 10000, NULL, 1, &MG_task);
}
extern int mginfo[4];

void PlayLeftRigth(int angle1, int angle2, int duration) {
    mginfo[0] = angle1;
    mginfo[1] = angle2;
    mginfo[2] = angle2 > angle1 ? 1 : -1;
    mginfo[3] = duration / abs(angle2 - angle1);

    xTaskCreate([](void* pvParameters) {
        for (;;) {
            for (int i = mginfo[0]; i != mginfo[1]; i += mginfo[2]) {
                mata.write(i);
                vTaskDelay(mginfo[3] * portTICK_PERIOD_MS);
            }
            for (int i = mginfo[1]; i != mginfo[0]; i -= mginfo[2]) {
                mata.write(i);
                vTaskDelay(mginfo[3] * portTICK_PERIOD_MS);
            }
        }
    },
                "MG90", 10000, NULL, 1, &MG_task);
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

extern bool wave;

void PlayWave(int angle1, int angle2, int duration) {
    if (!wave) {
        PlayAngle(angle1, duration);
        if (angle1 == mata.read()) wave = 1;
    }
    if (wave) {
        PlayAngle(angle2, duration);
        if (angle2 == mata.read()) wave = 0;
    }
}

void MG90::PlayAngle(int angle, int duration) {
    if (angle < 0) {
        angle = 0;
    } else if (angle > 180) {
        angle = 180;
    }
    this->target1 = angle;
    this->duration = duration;
    this->mode = PLAY_ANGLE;
    this->isDone = false;
}

void MG90::PlayWave(int angle1, int angle2, int duration) {
    this->target1 = angle1;
    this->target2 = angle2;
    this->duration = duration;
    this->mode = PLAY_WAVE;
    this->isDone = false;
}

void MG90::loop() {
    if (!this->isDone) {
        if (this->mode == PLAY_ANGLE) {
            int direction = this->target1 > read() ? 1 : -1;
            int lastMove = millis();
            float interval = duration / abs(this->target1 - read());
            for (int i = read(); i != this->target1;) {
                if (millis() - lastMove > interval) {
                    i += direction;
                    write(i);
                    lastMove = millis();
                }
            }
            if (read() == this->target1 - 1 || read() == this->target1 + 1) {
                this->isDone = true;
            }
        } else if (this->mode == PLAY_WAVE) {
            PlayWave(this->target1, this->target2, this->duration);
            this->isDone = true;
        }
    }
}

void MG90::MoveWithoutDelay(int minAngle, int maxAngle, int speed) {
    static unsigned long lastUpdate = 0;
    static int direction = 1;

    if (millis() - lastUpdate > speed) {
        int currentAngle = read();

        if (currentAngle >= maxAngle) {
            direction = -1;
        } else if (currentAngle <= minAngle) {
            direction = 1;
        }

        write(currentAngle + direction);
        lastUpdate = millis();
    }
}