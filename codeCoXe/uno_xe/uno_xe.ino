/**
*thu tín hiệu khi sắp có đèn đỏ,có xe từ hướng khác đến
*phát tín hiệu khi đến giao lộ // phát mã là biển số xe
*/

#include <IRremote.h>

const int bienSoXe = 68;

unsigned long lastTime = millis();
unsigned long lastTime2 = millis();
unsigned long timeCoiChoDenDo = millis();
unsigned long timeCoiChoXeDiQua = millis();

const int IR_RECEIVE_PIN = 2;    // Pin used to connect the IR receiver module (IR1838)
const int IR_TRANSMIT_PIN = 10;  // Pin used to connect the IR LED for transmission
const int coi = 9;
const int denXanh = 4;
const int denDo = 5;
const int denVang = 6;

bool checkCoi = 0;

IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend(IR_TRANSMIT_PIN);  // Create an IRsend object for IR transmission
decode_results results;

void setup() {
  Serial.begin(9600);
  Serial.println("set");
  irrecv.enableIRIn();  // Bắt đầu nhận tín hiệu hồng ngoại
  Serial.println("IR Receiver initialized");
  Serial.println("set2");
  pinMode(IR_TRANSMIT_PIN, OUTPUT);
  Serial.println("set3");
  pinMode(coi, OUTPUT);
  pinMode(denDo, OUTPUT);
  pinMode(denXanh, OUTPUT);
  pinMode(denVang, OUTPUT);

  digitalWrite(coi, HIGH);
  digitalWrite(denXanh, LOW);
  digitalWrite(denDo, LOW);
  digitalWrite(denVang, LOW);

  delay(200);

  digitalWrite(coi, LOW);
  digitalWrite(denXanh, HIGH);
}
void xuLiTinHieuNhan(long value) {
  //có xe
  if (value == 122222 || value == 222222) {
    digitalWrite(denDo, 0);
    digitalWrite(denXanh, 0);
    digitalWrite(denVang, 1);
    digitalWrite(coi, 1);
    delay(200);
    digitalWrite(coi, 0);
    delay(200);
    digitalWrite(coi, 1);
    delay(200);
    digitalWrite(coi, 0);
    delay(200);
    digitalWrite(denDo, 0);
    digitalWrite(denXanh, 1);
    digitalWrite(denVang, 0);
  } else if ((value == 244444 || value == 144444)) {
    if (millis() - timeCoiChoDenDo > 300)  //&&checkCoi==0)
    {
      //
      digitalWrite(denDo, 1);
      digitalWrite(denXanh, 0);
      digitalWrite(denVang, 0);
      timeCoiChoDenDo = millis();
      digitalWrite(coi, 1);
      checkCoi = 1;
      delay(1000);
      digitalWrite(coi, 0);
      timeCoiChoDenDo = millis();
      delay(2000);
      digitalWrite(denDo, 0);
      digitalWrite(denXanh, 1);
      digitalWrite(denVang, 0);
    }




  } else {
    delay(100);
  }
  // if (millis()-timeCoiChoDenDo>1000&&checkCoi==1)
  //     {
  //       // lastTime=millis();
  //       digitalWrite(coi,0);timeCoiChoDenDo=millis();
  //        digitalWrite(denDo, 0);
  //   digitalWrite(denXanh, 1);
  //   digitalWrite(denVang, 0);
  //     }
}
void loop() {
  delay(20);
  long value=0;
  if (irrecv.decode(&results)) {
     value = results.value;
    // Serial.println(value, DEC);
    if (value!=68){
    Serial.println(value);
    xuLiTinHieuNhan(value);
    }
    irrecv.resume();
  }

  if (millis() - lastTime > 300) {
    irsend.sendSony(bienSoXe, 25);
    delay(20);
    lastTime = millis();
  }
}
