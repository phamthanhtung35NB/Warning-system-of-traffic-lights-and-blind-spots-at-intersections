#include <IRremote.h>
const int RECV_PIN = 2;
const int pinLed1 = 3;
const int pinLed2 = 4;
const int pinLed3 = 5;
const int pinLed4 = 6;
unsigned long lastTime = millis();
//=================================================
void setup() {
  Serial.begin(9600);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  digitalWrite(pinLed1,LOW);
  digitalWrite(pinLed2,LOW);
  digitalWrite(pinLed3,LOW);
  digitalWrite(pinLed4,LOW);
  //Khởi động bộ thu
  IrReceiver.begin(RECV_PIN, true, 13); 
}
//=================================================
void loop() {
  if (IrReceiver.decode()) {
    uint32_t dataRemote = IrReceiver.decodedIRData.decodedRawData;
    if(dataRemote>0){
      Serial.println(dataRemote);
      if (millis() - lastTime > 250) {
        switch(dataRemote){
          case 3125149440://so1
            digitalWrite(pinLed1, !digitalRead(pinLed1));
          break;
          case 3108437760://so2
            digitalWrite(pinLed2, !digitalRead(pinLed2));
          break;
          case 3091726080://so3
            digitalWrite(pinLed3, !digitalRead(pinLed3));
          break;
          case 3141861120://so4
            digitalWrite(pinLed4, !digitalRead(pinLed4));
          break;
          case 3910598400://phím * Tắt hết
            digitalWrite(pinLed1, LOW);
            digitalWrite(pinLed2, LOW);
            digitalWrite(pinLed3, LOW);
            digitalWrite(pinLed4, LOW);
          break;
          case 4061003520://Phím # Bật hết
            digitalWrite(pinLed1, HIGH);
            digitalWrite(pinLed2, HIGH);
            digitalWrite(pinLed3, HIGH);
            digitalWrite(pinLed4, HIGH);
          break;
        }
      }
    }
    lastTime = millis();
    IrReceiver.resume(); // Cho phép nhận giá trị tiếp theo
  }
}
