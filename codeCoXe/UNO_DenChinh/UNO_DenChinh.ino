/**
*KHI CÓ XE - UNO CHÍNH
*/

#include <SoftwareSerial.h>
SoftwareSerial BT(4, 12);  //Rx/Tx
#include <IRremote.h>
#include <String.h>

//thu 2
const int IR_RECEIVE_PIN02 = 2;
IRrecv irrecv02(IR_RECEIVE_PIN02);

//phast 1
const int IR_TRANSMIT_PIN01 = 5;
IRsend irsend01(IR_TRANSMIT_PIN01);
//phast 2
const int IR_TRANSMIT_PIN02 = 3;
IRsend irsend02(IR_TRANSMIT_PIN02);


decode_results results02;

unsigned long timeCheckThu2 = millis();

unsigned long lastTime2 = millis();

bool isVang = false;

unsigned long lastTimeDen = -10000;

const int denXanh1 = 6;
const int denVang1 = 7;
const int denDo1 = 8;

const int denXanh2 = 9;
const int denVang2 = 10;
const int denDo2 = 11;

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  irrecv02.enableIRIn();
  // irrecv.enableIRIn();// Bắt đầu nhận tín hiệu hồng ngoại
  Serial.println("IR Receiver initialized");
  pinMode(IR_TRANSMIT_PIN01, OUTPUT);
  pinMode(IR_TRANSMIT_PIN02, OUTPUT);

  pinMode(denDo1, OUTPUT);
  pinMode(denXanh1, OUTPUT);
  pinMode(denVang1, OUTPUT);

  pinMode(denDo2, OUTPUT);
  pinMode(denXanh2, OUTPUT);
  pinMode(denVang2, OUTPUT);

  digitalWrite(denXanh1, LOW);
  digitalWrite(denVang1, HIGH);
  digitalWrite(denDo1, LOW);
  digitalWrite(denXanh2, LOW);
  digitalWrite(denVang2, HIGH);
  digitalWrite(denDo2, LOW);

  delay(600);

  digitalWrite(denVang1, LOW);
  digitalWrite(denVang2, LOW);
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
    return incomingByte;
  }
}
//thu tín hiệu đèn 2
String thuHongNgoai2() {
  String string = "1";
  if (irrecv02.decode(&results02)) {
    string = (String)results02.value;
    // Serial.println(string);
    irrecv02.resume();
  }
  return string;
}
void viewDen() {
  if (millis() - lastTimeDen > 1000) {
    if (isVang == false) {
      Serial.println("vang - sáng");
      digitalWrite(denXanh1, LOW);
      digitalWrite(denVang1, HIGH);
      digitalWrite(denDo1, LOW);
      digitalWrite(denXanh2, LOW);
      digitalWrite(denVang2, HIGH);
      digitalWrite(denDo2, LOW);
      isVang = true;
    } else {
      Serial.println("vang - tat");
      digitalWrite(denXanh1, LOW);
      digitalWrite(denVang1, LOW);
      digitalWrite(denDo1, LOW);
      digitalWrite(denXanh2, LOW);
      digitalWrite(denVang2, LOW);
      digitalWrite(denDo2, LOW);
      isVang = false;
    }
    lastTimeDen = millis();
  }
}
void loop() {
  viewDen();
  // Phát có xe 2;
  if (thuHongNgoai1() == 'K') {

    Serial.println("phat co xe 2");
    phatCoXe2();
  }
  // irsend02.sendSony("123", 30);
  // delay(20);

  // if (millis() - lastTime > 300)
  // {
  // phatCoXe2();
  // lastTime=millis();
  // }


  //nếu có xe đến đèn 2
  String nn = thuHongNgoai2();
  Serial.println(nn);
  if (nn == "68") {
    if (millis() - lastTime2 > 300) {
      Serial.println("phat co xe 1");
      phatCoXe1();
      lastTime2 = millis();
    }
  }
  // irsend01.sendSony(0, 22);
  // irsend02.sendSony(0, 22);
  // delay(20);
}