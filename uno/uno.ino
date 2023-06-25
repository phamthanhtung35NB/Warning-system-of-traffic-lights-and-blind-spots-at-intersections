/**
*phát tín hiệu khi sắp có đèn đỏ
*nhận tín hiệu xe đến giao lộ
*/
#include <IRremote.h>
const int IR_RECEIVE_PIN01 = 2; //thu
const int IR_TRANSMIT_PIN01 = 3; //phast

const int IR_RECEIVE_PIN02 = 4; //thu 2
const int IR_TRANSMIT_PIN02 = 5; //phast 2


IRrecv irrecv(IR_RECEIVE_PIN01);
IRsend irsend(IR_TRANSMIT_PIN01);  // Tạo đối tượng IRSEND để truyền IR

IRrecv irrecv02(IR_RECEIVE_PIN02);
IRsend irsend02(IR_TRANSMIT_PIN02); 


decode_results results;
decode_results results02;

unsigned long timeCheckThu = millis();
unsigned long timeCheckThu2 = millis();
unsigned long lastTimeDen = -10000;

const int denXanh1=6;
const int denVang1=7;
const int denDo1=8;

const int denXanh2=9;
const int denVang2=10;
const int denDo2=11;

const int timeXanh1=10000/2;   //1s=1000mls         //
const int timeXanh2=10000/2;
const int timeVang=3000/2;

bool denDo1 = false;
bool denDo2 = true;
bool denVang1 = false;
bool denVang2 = false;
bool coXe1 = false;
bool coXe2 = false;

int maHongNgoaiNhan1=0;
int maHongNgoaiNhan2=0;
void setup()
{
  Serial.begin(9600);
  // irrecv.enableIRIn();// Bắt đầu nhận tín hiệu hồng ngoại
  Serial.println("IR Receiver initialized");
  pinMode(IR_TRANSMIT_PIN01, OUTPUT);
  pinMode(IR_TRANSMIT_PIN02, OUTPUT);

  pinMode(denDo1, OUTPUT);
  pinMode(denXanh1, OUTPUT);
  pinMode(denVang1, OUTPUT);

  digitalWrite(denDo1, LOW);
  digitalWrite(denXanh1, HIGH);
  digitalWrite(denVang1, LOW);
}
void xanh1(){
  //xanh dai on-đỏ ngắn on
  Serial.println("xanh1");
  digitalWrite( denXanh1, HIGH); 
  digitalWrite( denVang1,LOW); 
  digitalWrite( denDo1, LOW); 
  digitalWrite( denXanh2, LOW); 
  digitalWrite( denVang2, LOW); 
  digitalWrite( denDo2, HIGH);
}
void vang1(){
  //vang dài on- dỏ ngắn on    
  Serial.println("vang1");                   
  digitalWrite( denXanh1, LOW); 
  digitalWrite( denVang1,HIGH); 
  digitalWrite( denDo1, LOW); 
  digitalWrite( denXanh2, LOW); 
  digitalWrite( denVang2, LOW); 
  digitalWrite( denDo2, HIGH);
}
void xanh2(){
  //xanh ngan on - do dai on  
  Serial.println("xanh2");                 
  digitalWrite( denXanh1, LOW); 
  digitalWrite( denVang1,LOW); 
  digitalWrite( denDo1, HIGH); 
  digitalWrite( denXanh2, HIGH); 
  digitalWrite( denVang2, LOW); 
  digitalWrite( denDo2,LOW); 
}
void vang2(){
  //vang ngan on-do dai on
  Serial.println("vang 2");
  digitalWrite( denXanh1, LOW); 
  digitalWrite( denVang1,LOW); 
  digitalWrite( denDo1, HIGH); 
  digitalWrite( denXanh2, LOW); 
  digitalWrite( denVang2, HIGH); 
  digitalWrite( denDo2, LOW);
}
void phatDenDo1(){
  irsend.sendSony(4321, 20);
  delay(100);
}
void phatCoXe1(){
  irsend.sendSony(1111, 20);
  delay(100);
}
void phatDenDo2(){
  irsend02.sendSony(4321, 20);
  delay(100);
}
void phatCoXe2(){
  irsend02.sendSony(1111, 20);
  delay(100);
}
int thuHongNgoai1(){
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    // Serial.println(value, DEC);
    Serial.println(value);
    irrecv.resume();
    return value;
  }
}
int thuHongNgoai2(){
  if (irrecv02.decode(&results02))
  {
    unsigned long value = results.value;
    // Serial.println(value, DEC);
    Serial.println(value);
    irrecv02.resume();
    return value;
  }
}
void viewDen(){
  if (denDo2 == true && denVang1 == false && denVang2 == false && denDo1 == false)
  {
    xanh1();
    phatDenDo2();
  }
  else if (denDo2 == true && denVang1 == true && denVang2 == false && denDo1 == false)
  {
    vang1();
  }
  else if (denDo2 == false && denVang1 == false && denVang2 == false && denDo1 == true)
  {
    xanh2();
    phatDenDo1();
  }
  else if (denDo2 == false && denVang1 == false && denVang2 == true && denDo1 == true)
  {
    vang2();
  }
}
void loop()
{
  // /vang 1
  if (millis() -  lastTimeDen>timeXanh1&&denDo2==true)
  {

    denDo1 = false;
    denDo2 = true;
    denVang1 = true;
    denVang2 = false;
    lastTimeDen = millis();
  }
  // xanh 2
  else if (millis() -  lastTimeDen>timeVang&&denVang1==true)
  {
    denDo1 = true;
    denDo2 = false;
    denVang1 = false;
    denVang2 = false;
    lastTimeDen = millis();
  }
  //vàng 2
  else if (millis() -  lastTimeDen>timeXanh2&&denDo1==true)
  {
    denDo1 = true;
    denDo2 = false;
    denVang1 = false;
    denVang2 = true;
    lastTimeDen = millis();
  }
  // xanh1
  else if (millis() -  lastTimeDen>timeVang&&denVang2==true)
  {
    denDo1 = false;
    denDo2 = true;
    denVang1 = false;
    denVang2 = false;
    lastTimeDen = millis();
  }
  viewDen();
  if (millis()-timeCheckThu>250)
  {
    maHongNgoaiNhan1=thuHongNgoai1();
    maHongNgoaiNhan2=thuHongNgoai2();
  }
  //nếu có xe đến 1
  phatCoXe2();
  //nếu có xe đến 2
  phatCoXe1();

  
  // if (millis() - timeCheckThu1 > 500)
  // {
  //   digitalWrite(coi, 0); 
  // }
  // if (millis() - timeCheckThu1 > 2000)
  // {
  //   digitalWrite(coi, 0);
  //   digitalWrite(denDo, 0);
  //   digitalWrite(denXanh, 1);
  //   digitalWrite(denVang, 0);
  // }
  
}