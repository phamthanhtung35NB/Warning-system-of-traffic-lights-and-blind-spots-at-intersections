/**
*phát tín hiệu khi sắp có đèn đỏ
*nhận tín hiệu xe đến giao lộ
*/

// #include <IRremote.h>
// const int RECV_PIN = 2;

// unsigned long lastTime = millis();
// //=================================================  
// void setup() {
//   Serial.begin(9600);
//   //Khởi động bộ thu
//   IrReceiver.begin(RECV_PIN, true, 13); 
//   Serial.println("dataRemote");
// }
// //=================================================
// void loop() {
//   if (IrReceiver.decode()) {
//     uint32_t dataRemote = IrReceiver.decodedIRData.decodedRawData;
//     if(dataRemote>0){
//       Serial.println(dataRemote);
//       if (millis() - lastTime > 250) {
//         switch(dataRemote){
//           case 64260://so1
//             Serial.println("20o");
//           break;
         
//         }
//       }
//     }
//     lastTime = millis();
//     IrReceiver.resume(); // Cho phép nhận giá trị tiếp theo
//   }
// }
#include <IRremote.h>
unsigned long lastTime = millis();
#include <IRremote.h>
const int IR_RECEIVE_PIN01 = 2; //thu
const int IR_TRANSMIT_PIN01 = 3; //phast
IRrecv irrecv(IR_RECEIVE_PIN01);
IRsend irsend(IR_TRANSMIT_PIN01);  // Create an IRsend object for IR transmission

const int IR_RECEIVE_PIN02 = 4; //thu
const int IR_TRANSMIT_PIN02 = 5; //phast
IRrecv irrecv02(IR_RECEIVE_PIN02);
IRsend irsend02(IR_TRANSMIT_PIN02); 
decode_results results;

const int denXanh1=6;
const int denVang1=7;
const int denDo1=8;
const int denXanh2=9;
const int denVang2=10;
const int denDo2=11;

const int timeXanh1=10000/2;   //1s=1000mls         //
const int timeXanh2=10000/2;
const int timeVang=3000/2;
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
void loop()
{
  
  // if (irrecv.decode(&results))
  // {
  //   unsigned long value = results.value;
  //   // Serial.println(value, DEC);
  //   Serial.println(value);
  //   irrecv.resume();
  //   if (value=4321&&millis()-lastTime>3000)
  //   {
  //     digitalWrite(coi, 1);
  //     digitalWrite(denDo, 1);
  //     digitalWrite(denXanh, 0);
  //     digitalWrite(denVang, 0);
  //     lastTime=millis();
  //   } 
  // }
  xanh1();
  irsend.sendSony(4321, 20);
  delay(100);
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
  
}