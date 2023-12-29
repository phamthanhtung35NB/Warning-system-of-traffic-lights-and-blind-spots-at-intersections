/**
*phát tín hiệu khi sắp có đèn đỏ
*nhận tín hiệu xe đến giao lộ

đèn đỏ 144444 244444
có xe 122222 222222

denXanh1=6;
denVang1=7;
denDo1=8;

denXanh2=9;
denVang2=10;
denDo2=11;

timeXanh1=10000/2;   //1s=1000mls 
timeXanh2=10000/2;
timeVang=3000/2;

*/

#include <SoftwareSerial.h>
SoftwareSerial BT(4, 12);  //Rx/Tx
#include <IRremote.h>
#include <String.h>

const int IR_RECEIVE_PIN02 = 2;   //thu 2
const int IR_TRANSMIT_PIN02 = 3;  //phast 2
const int IR_TRANSMIT_PIN01 = 5;  //phast 1

IRrecv irrecv02(IR_RECEIVE_PIN02);
IRsend irsend02(IR_TRANSMIT_PIN02);

IRsend irsend01(IR_TRANSMIT_PIN01);

decode_results results02;

unsigned long timeCheckThu2 = millis();

unsigned long lastTime2 = millis();

unsigned long lastTimeDen = -10000;

const int denVang1 = 7;

const int denVang2 = 10;

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  // irrecv.enableIRIn();// Bắt đầu nhận tín hiệu hồng ngoại
  Serial.println("IR Receiver initialized");
  pinMode(IR_TRANSMIT_PIN01, OUTPUT);
  pinMode(IR_TRANSMIT_PIN02, OUTPUT);
}


void phatCoXe1() {
  irsend01.sendSony(122222, 30);
  delay(20);
}

void phatCoXe2() {
  irsend02.sendSony(222222, 30);
  delay(20);
}
//thu tín hiệu tu arduino
char thuHongNgoai1() {
  if (BT.available() > 0) {
    char incomingByte = BT.read();  // Đọc dữ liệu từ cổng RX
    //Serial.print("GiaTri: ");

    // Serial.println(incomingByte);

    // In dữ liệu đã đọc ra Serial Monitor
    return incomingByte;
    // return 0;
  }
}
//thu tín hiệu đèn 2
int thuHongNgoai2() {
  int kQua = 0;
  if (irrecv02.decode(&results02)) {
    kQua = results02.value;
    irrecv02.resume();
  }
  return kQua;
}
void viewDen() {
}
void loop() {
  viewDen();
  if (thuHongNgoai1() == 'K') {
    
    Serial.println("phat co xe 2");
    phatCoXe2();
  }
irsend02.sendSony("123", 30);
  delay(20);
  // if (millis() - lastTime > 300)
  // {
  // phatCoXe2();
  // lastTime=millis();
  // }
int nn=thuHongNgoai2();
Serial.println(nn);
  //nếu có xe đến đèn 2
  if (nn == 68) {
    // if (millis() - lastTime2 > 300)
    {
      Serial.println("phat co xe 1");
      phatCoXe1();
      // lastTime2=millis();
    }
  }
  // irsend01.sendSony(0, 22);
  // irsend02.sendSony(0, 22);
  // delay(20);
}