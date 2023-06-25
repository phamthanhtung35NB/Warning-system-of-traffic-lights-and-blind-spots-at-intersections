/**
*thu tín hiệu khi sắp có đèn đỏ
*phát tín hiệu khi đến giao lộ
*/

unsigned long lastTime = millis();
#include <IRremote.h>

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
  digitalWrite(coi, LOW);
  digitalWrite(denDo, LOW);
  digitalWrite(denXanh, HIGH);
  digitalWrite(denVang, LOW);
}

void loop()
{
  
  if (irrecv.decode(&results))
  {
    unsigned long value = results.value;
    // Serial.println(value, DEC);
    Serial.println(value);
    irrecv.resume();
    if (value=4321&&millis()-lastTime>3000)
    {
      digitalWrite(coi, 1);
      digitalWrite(denDo, 1);
      digitalWrite(denXanh, 0);
      digitalWrite(denVang, 0);
      lastTime=millis();
    } 
  }
  irsend.sendSony(1111, 20);
  delay(600);
  if (millis() - lastTime > 500)
  {
    digitalWrite(coi, 0); 
  }
  if (millis() - lastTime > 2000)
  {
    digitalWrite(coi, 0);
    digitalWrite(denDo, 0);
    digitalWrite(denXanh, 1);
    digitalWrite(denVang, 0);
  }
  
}

