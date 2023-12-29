/**
 * KHI CÓ XE - UNO PHỤ
*/
#include <IRremote.h>
#include <String.h>

const int IR_RECEIVE_PIN02 = 2;  //thu 2
// const int IR_TRANSMIT_PIN02 = 3;  //phast 2


IRrecv irrecv02(IR_RECEIVE_PIN02);
// IRsend irsend02(IR_TRANSMIT_PIN02);

decode_results results02;

// unsigned long timeCheckThu2 = millis();

// unsigned long lastTime2 = millis();

// unsigned long lastTimeDen = -10000;

void setup() {
  Serial.begin(9600);
  // irrecv.enableIRIn();// Bắt đầu nhận tín hiệu hồng ngoại
  irrecv02.enableIRIn();
  Serial.println("IR Receiver initialized");
  // pinMode(IR_TRANSMIT_PIN01, OUTPUT);
  // pinMode(IR_TRANSMIT_PIN02, OUTPUT);
}


void loop() {

  if (irrecv02.decode(&results02)) {
    String string = "1";
    string = (String)results02.value;
    // Serial.println(string);
    if (string == "68") {
      Serial.println("K");
    }
    irrecv02.resume();
  }
}