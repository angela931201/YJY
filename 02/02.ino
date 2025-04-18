// 定義引腳
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 11;

// 儲存LED狀態
bool ledState = false;

// 儲存上次按鈕狀態
int lastButtonState = LOW;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 超音波傳感器測距
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // 計算距離 (cm)

  // 根據距離調整LED亮度
  int brightness = map(distance, 0, 200, 255, 0); // 距離越遠亮度越高，越近越暗
  brightness = constrain(brightness, 0, 255); // 限制亮度範圍

  analogWrite(ledPin, brightness);

  delay(100); // 延遲以穩定讀數
}