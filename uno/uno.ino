/**
*phát tín hiệu khi sắp có đèn đỏ
*nhận tín hiệu xe đến giao lộ
*/

#include <IRremote.h>
const int RECV_PIN = 2;

unsigned long lastTime = millis();
//=================================================
void setup() {
  Serial.begin(9600);
  //Khởi động bộ thu
  IrReceiver.begin(RECV_PIN, true, 13); 
  Serial.println("dataRemote");
}
//=================================================
void loop() {
  if (IrReceiver.decode()) {
    uint32_t dataRemote = IrReceiver.decodedIRData.decodedRawData;
    if(dataRemote>0){
      Serial.println(dataRemote);
      if (millis() - lastTime > 250) {
        switch(dataRemote){
          case 64260://so1
            Serial.println("20o");
          break;
         
        }
      }
    }
    lastTime = millis();
    IrReceiver.resume(); // Cho phép nhận giá trị tiếp theo
  }
}
