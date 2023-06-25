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

const int IR_RECEIVE_PIN = 2;  // Chân số 2 được sử dụng để kết nối cảm biến IR1838

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();  // Bắt đầu nhận tín hiệu hồng ngoại
  Serial.println("------111-");
}

void loop()
{
  // if (IrReceiver.decode()) {
  //   uint32_t dataRemote = IrReceiver.decodedIRData.decodedRawData;
  //   if(dataRemote>0){
  //     Serial.println(dataRemote);}}
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    Serial.println("-------");
    Serial.print("Mã nhận được: ");
    // Serial.println(value, HEX);
    Serial.println(value, DEC);  // Hiển thị giá trị dưới dạng số thập phân
    // Serial.println(value, BIN);  // Hiển thị giá trị dưới dạng số nhị phân
    // Serial.println(value, OCT);  // Hiển thị giá trị dưới dạng số bát phân
    // Serial.println(value, BYTE); // Hiển thị giá trị dưới dạng số nguyên 8-bit

    irrecv.resume();  // Tiếp tục nhận tín hiệu hồng ngoại
  }
}
