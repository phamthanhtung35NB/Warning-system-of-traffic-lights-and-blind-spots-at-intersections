/**
*thu tín hiệu khi sắp có đèn đỏ,có xe từ hướng khác đến
*phát tín hiệu khi đến giao lộ // phát mã là biển số xe
*/

#include <IRremote.h>

const int bienSoXe = 56789;

unsigned long lastTime = millis();
unsigned long lastTime2 = millis();
unsigned long timeCoiChoDenDo = millis();
unsigned long timeCoiChoXeDiQua = millis();

const int IR_RECEIVE_PIN = 2;    // Pin used to connect the IR receiver module (IR1838)
const int IR_TRANSMIT_PIN = 10;   // Pin used to connect the IR LED for transmission
const int coi =3;
const int denXanh=4;
const int denDo=5;
const int denVang=6;
IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend(IR_TRANSMIT_PIN);  // Create an IRsend object for IR transmission
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();// Bắt đầu nhận tín hiệu hồng ngoại
  Serial.println("IR Receiver initialized");
  pinMode(IR_TRANSMIT_PIN, OUTPUT);
  pinMode(coi, OUTPUT);
  pinMode(denDo, OUTPUT);
  pinMode(denXanh, OUTPUT);
  pinMode(denVang, OUTPUT);

  digitalWrite(coi, HIGH);
  digitalWrite(denXanh, LOW);
  digitalWrite(denDo, LOW);
  digitalWrite(denVang, LOW);

  delay(500);

  digitalWrite(coi, LOW);
  digitalWrite(denXanh, HIGH);
}
void xuLiTinHieuNhan(unsigned long value){
  if (value==144444||value==244444)
    {
      if (millis()-timeCoiChoDenDo>10000)
      {
        timeCoiChoDenDo=millis();
        digitalWrite(coi, 1);
      }
      
      if (millis()-lastTime>1000)
      {
        digitalWrite(coi,0);
        lastTime=millis();
      }
      digitalWrite(denDo, 1);
      digitalWrite(denXanh, 0);
      digitalWrite(denVang, 0);
    }
  else if (value==111111||value==211111)
  {
    if (millis()-timeCoiChoXeDiQua>1000)
      {
        timeCoiChoXeDiQua=millis();
        digitalWrite(coi, 1);
      }
      
      if (millis()-lastTime2>500)
      {
        digitalWrite(coi,0);
        lastTime2=millis();
      }
      digitalWrite(denDo, 0);
      digitalWrite(denXanh, 0);
      digitalWrite(denVang, 1);
  }else
  {
    digitalWrite(denDo, 0);
    digitalWrite(denXanh, 1);
    digitalWrite(denVang, 0);
  }
}
void loop()
{
  
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    // Serial.println(value, DEC);
    Serial.println(value);
    xuLiTinHieuNhan(value);
    irrecv.resume();
  }
  delay(600);
  // if (millis() - lastTime > 500)
  // {
  //   digitalWrite(coi, 0); 
  // }
  // if (millis() - lastTime > 2000)
  // {
  //   digitalWrite(coi, 0);
  //   digitalWrite(denDo, 0);
  //   digitalWrite(denXanh, 1);
  //   digitalWrite(denVang, 0);
  // }
  irsend.sendSony(bienSoXe, 20);
}

