/**
*thu tín hiệu khi sắp có đèn đỏ
*phát tín hiệu khi đến giao lộ
*/
// #include <IRremote.h>
// #include <IRremote.h>

// #define IR_LED_PIN 3

// IRsend irsend(IR_LED_PIN);

// void setup()
// {
//   Serial.begin(9600);
//   irsend.enableIROut(38);  // Thiết lập tần số là 38kHz
// }

// void loop()
// {
//   irsend.sendSony(64260, 16);  // Gửi mã 64260, 16 bits
//   delay(500);  // Chờ 0.5 giây trước khi gửi mã tiếp theo
// }
// #include <IRremote.h>

// #define IR_LED_PIN 9

// IRsend irsend(IR_LED_PIN);

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   irsend.sendSony(64260, 20); // Gửi mã 64260 với độ dài 20 bit
//   delay(1000); // Đợi 1 giây trước khi gửi lại
// }
#include <IRremote.h>

#define IR_LED_PIN 10

IRsend irsend(IR_LED_PIN);
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("-------");
  Serial.println("12345");
  irsend.sendSony(12345, 32);  // Gửi mã Sony (64260) trong 20 bit
  delay(500);
  Serial.println("-------");
  Serial.println("10101");
  irsend.sendSony(10101, 32);  // Gửi mã Sony (64260) trong 20 bit
  delay(500);
}
