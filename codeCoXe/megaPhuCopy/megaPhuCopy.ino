
#include <IRremote.h>
#include <String.h>

const int IR_RECEIVE_PIN02 = 2;   //thu 2
// const int IR_TRANSMIT_PIN02 = 3;  //phast 2


IRrecv irrecv02(IR_RECEIVE_PIN02);
// IRsend irsend02(IR_TRANSMIT_PIN02);

decode_results results02;

// unsigned long timeCheckThu2 = millis();

// unsigned long lastTime2 = millis();

// unsigned long lastTimeDen = -10000;


// bool TFdenVang1 = false;
// bool TFdenVang2 = false;
// bool coXe1 = false;
// bool coXe2 = false;

int maHongNgoaiNhan2 = 0;
void setup() {
  // BT.begin(9600);
  Serial.begin(9600);
  // irrecv.enableIRIn();// Bắt đầu nhận tín hiệu hồng ngoại
  irrecv02.enableIRIn();
  Serial.println("IR Receiver initialized");
  // pinMode(IR_TRANSMIT_PIN01, OUTPUT);
  // pinMode(IR_TRANSMIT_PIN02, OUTPUT);
}

// void phatCoXe2() {
//   irsend02.sendSony(222222, 30);
//   delay(20);
// }
//thu tín hiệu đèn 2
// unsigned long thuHongNgoai2() {
  
//   if (irrecv02.decode(&results02)) {
//     unsigned long value = results02.value;
//     Serial.println(value);
//     irrecv02.resume();
    
//     return value;
//   }
// }

void loop() {

  if (irrecv02.decode(&results02)) {
    String string = "1";
     string=(String)results02.value;
  // Serial.println(string);
  if(string=="68"){
    Serial.println("K");
  }
    irrecv02.resume();
  }
}