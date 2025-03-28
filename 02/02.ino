#include <NewPing.h>

// 定義引腳
#define TRIGGER_PIN 7 // 超音波傳感器的觸發引腳
#define ECHO_PIN 6    // 超音波傳感器的回聲引腳
#define LED_PIN 9     // LED 燈的引腳
#define BUTTON_PIN 8  // 按鈕的引腳

// 定義參數
#define MAX_DISTANCE 200 // 最大測量距離（單位：厘米）

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool buttonPressed = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // 讀取按鈕狀態
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // 消抖
    if (!buttonPressed) {
      buttonPressed = true;

      // 測量距離
      int distance = sonar.ping_cm();
      Serial.print("距離: ");
      Serial.print(distance);
      Serial.println("cm");

      // 根據距離調整 LED 亮度
      if (distance > 0 && distance <= MAX_DISTANCE) {
        int brightness = map(distance, 0, MAX_DISTANCE, 255, 0); // 距離越近亮度越高
        analogWrite(LED_PIN, brightness);
      } else {
        analogWrite(LED_PIN, 0); // 超出範圍時關閉 LED
      }
    }
  } else {
    buttonPressed = false;
  }
}