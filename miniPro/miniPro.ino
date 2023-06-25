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

const int IR_RECEIVE_PIN = 2;    // Pin used to connect the IR receiver module (IR1838)
const int IR_TRANSMIT_PIN = 10;   // Pin used to connect the IR LED for transmission

IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend(IR_TRANSMIT_PIN);  // Create an IRsend object for IR transmission
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("IR Receiver initialized");
  pinMode(IR_TRANSMIT_PIN, OUTPUT);  // Set IR transmit pin as output
  pinMode(3, OUTPUT);  // Set IR transmit pin as output
  
}

void loop()
{
  digitalWrite(3, 1);
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    Serial.println(value, DEC);
    irrecv.resume();
  }//Giải quyết dòng sau để truyền lại mã IR đã nhận được
    irsend.sendSony(111, 20);
    delay(600);
}

