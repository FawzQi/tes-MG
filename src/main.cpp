#include "main.h"

OLED displayRobot;

CRGB leds[2];
CRGB leds2[1];

uint8_t total_chunk = 0;
uint8_t received_chunk = 0;
uint32_t rchecksum = 0;
// CRGB leds2[1];

LedBender LED_left(0, leds);
LedBender LED_right(1, leds);
// LedBender LED_interface(0, leds2);

EasyButton mode_a(PIN_BUTTON1, 100);
EasyButton mode_b(PIN_BUTTON2, 100);
EasyButton trig(PIN_TRIG, 100);
Sound sound("VI-ROSE", true);
bool mx_status = false, xl_status = false;

Servo mata;

CRC32 crc;
int xi = 0;
void setup() {
    Serial.begin(115200);

    if (!SPIFFS.begin(true)) {
        Serial.println("[-] An Error has occurred while mounting SPIFFS");
        return;
    } else {
        Serial.println("[+] SPIFFS Mounted Successfully");
    }

    if (SPIFFS.exists("/active_bucket.json")) SPIFFS.remove("/active_bucket.json");
    setupDisplay();

    sound.start();
    initButton();
    esp_err_t result = initESPNow(ESP_MAC_INDEX, 2);
    DEBUG_PRINTF("[ESP-NOW] Init: %s\n", esp_err_to_name(result));

    DEBUG_PRINTF("[Main-Micro] Ready for Serial Communication\n");
    FastLED.addLeds<WS2812B, LED_PCB, GRB>(leds, 2);

    byte init_bucket[2] = {GET_SPIFFS_MOTION, 0};
    esp_now_send(mac_addresses[ESP_MAC_INDEX == 0 ? 2 : 3], init_bucket, sizeof(init_bucket));
    // FastLED.addLeds<WS2812B, LED_INTERFACE, GRB>(leds2, 1);

    LED_left.turnOn(CRGB::Purple);
    LED_right.turnOn(CRGB::Purple);
    TASK2::PlayMotion();
    // LED_interface.turnOn(CRGB::Red);
}

void loop() {
    if (millis() / 1000 > xi) {
        Serial.print("Time: ");
        Serial.println(xi);
        xi++;
    }
}
