/**
*phát tín hiệu khi sắp có đèn đỏ
*nhận tín hiệu xe đến giao lộ

đèn đỏ 144444 244444
có xe 111111 211111

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

///////////////////////////////////////////////
                                             //
const int timeXanh1=10000/2;   //1s=1000mls  //
const int timeXanh2=10000/2;                 //
const int timeVang=3000/2;                   //
                                             //
///////////////////////////////////////////////

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

unsigned long lastTime = millis();
unsigned long lastTime2 = millis();

unsigned long lastTimeDen = -10000;

const int denXanh1=6;
const int denVang1=7;
const int denDo1=8;

const int denXanh2=9;
const int denVang2=10;
const int denDo2=11;

bool TFdenDo1 = false;
bool TFdenDo2 = true;
bool TFdenVang1 = false;
bool TFdenVang2 = false;
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

  pinMode(denDo2, OUTPUT);
  pinMode(denXanh2, OUTPUT);
  pinMode(denVang2, OUTPUT);

  TFdenDo2==true;
  // digitalWrite(denDo1, LOW);
  // digitalWrite(denXanh1, HIGH);
  // digitalWrite(denVang1, LOW);
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
  irsend.sendSony(144444, 30);
  delay(20);
}
void phatCoXe1(){
  irsend.sendSony(122222, 30);
  delay(20);
}
void phatDenDo2(){
  irsend02.sendSony(244444, 30);
  delay(20);
}
void phatCoXe2(){
  irsend02.sendSony(222222, 30);
  delay(20);
}
//thu tín hiệu đèn 1
unsigned long thuHongNgoai1(){
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    // Serial.println(value, DEC);
    Serial.println(value);
    irrecv.resume();
    return value;
  }
}
//thu tín hiệu đèn 2
unsigned long thuHongNgoai2(){
  if (irrecv02.decode(&results02))
  {
    unsigned long value = results02.value;
    // Serial.println(value, DEC);
    Serial.println(value);
    irrecv02.resume();
    return value;
  }
}
void viewDen(){
  if (TFdenDo2 == true && TFdenVang1 == false 
  && TFdenVang2 == false && TFdenDo1 == false)
  {
    xanh1();
    // phatDenDo2();
  }
  else if (TFdenDo2 == true && TFdenVang1 == true 
  && TFdenVang2 == false && TFdenDo1 == false)
  {
    vang1();
  }
  else if (TFdenDo2 == false && TFdenVang1 == false 
  && TFdenVang2 == false && TFdenDo1 == true)
  {
    xanh2();
    // phatDenDo1();
  }
  else if (TFdenDo2 == false && TFdenVang1 == false 
  && TFdenVang2 == true && TFdenDo1 == true)
  {
    vang2();

  }
}
bool control_Led(){
  // xanh1->vang 1
  if (millis() -  lastTimeDen>timeXanh1&&TFdenDo2==true)
  {

    TFdenDo1 = false;
    TFdenDo2 = true;
    TFdenVang1 = true;
    TFdenVang2 = false;
    lastTimeDen = millis();
    return true;
  }
  // vang1->xanh 2
  else if (millis() -  lastTimeDen>timeVang&&TFdenVang1==true&&TFdenDo2==true)
  {
    TFdenDo1 = true;
    TFdenDo2 = false;
    TFdenVang1 = false;
    TFdenVang2 = false;
    lastTimeDen = millis();
    return true;
  }
  //xanh2->vàng 2
  else if (millis() -  lastTimeDen>timeXanh2&&TFdenDo1==true)
  {
    TFdenDo1 = true;
    TFdenDo2 = false;
    TFdenVang1 = false;
    TFdenVang2 = true;
    lastTimeDen = millis();
    return true;
  }
  //vang2-> xanh1
  else if (millis() -  lastTimeDen>timeVang&&TFdenVang2==true)
  {
    TFdenDo1 = false;
    TFdenDo2 = true;
    TFdenVang1 = false;
    TFdenVang2 = false;
    lastTimeDen = millis();
    return true;
  }
  return false;
}
void loop()
{
  if(control_Led()){
    viewDen();
  }
  if (TFdenDo2 == true && TFdenVang1 == false 
  && TFdenVang2 == false && TFdenDo1 == false)
  {
    phatDenDo2();
  }
  else if (TFdenDo2 == false && TFdenVang1 == false 
  && TFdenVang2 == false && TFdenDo1 == true)
  {
    phatDenDo1();
  }
  // if (millis()-timeCheckThu>250)
  // {
  //   //nếu có xe đến đèn 1
    int thuHN1=thuHongNgoai1();  
    int thuHN2=thuHongNgoai2();  
    if ((thuHN1!=122222&&thuHN1!=222222&&thuHN1!=144444&&thuHN1!=244444)||thuHN1<99999)
    {
      if (millis() - lastTime > 300)
      {
        phatCoXe2();
        lastTime=millis();
      }
    }
    //nếu có xe đến đèn 2
    if ((thuHN2!=122222&&thuHN2!=222222&&thuHN2!=144444&&thuHN2!=244444)||thuHN2<99999)
    {
      if (millis() - lastTime2 > 300)
      {
        phatCoXe1();
        lastTime2=millis();
      }
    }
  //   timeCheckThu=millis();
  // }

// irsend.sendSony(144444, 22);
//   delay(100);
//   irsend02.sendSony(244444, 22);
//   delay(100);
  

  
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