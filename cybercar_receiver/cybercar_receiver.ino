#include <esp_now.h>
#include <WiFi.h>

// define pins 
const int motorPinA1 = 4;
const int motorPinA2 = 5;
const int motorPinB1 = 6;
const int motorPinB2 = 7;

// data structure 
struct Data {
   int potValue;
}; 

// receiver callback function 
void onDataReceived(const uint8_t* mac, const uint8_t* incommingData, int len) {
  Data* receivedData = (Data*)incomingData;
  int potValue = receivedData->potValue;

   if (potValue < 1000) {
    digitalWrite(motorPinA1, LOW);
    digitalWrite(motorPinA2, HIGH);
    digitalWrite(motorPinB1, LOW);
    digitalWrite(motorPinB2, HIGH);
    } else if(potValue > 3000) {
    digitalWrite(motorPinA1, HIGH);
    digitalWrite(motorPinA2, LOW);
    digitalWrite(motorPinB1, HIGH);
    digitalWrite(motorPinB2, LOW);
    } else {
    digitalWrite(motorPinA1, LOW);
    digitalWrite(motorPinA2, LOW);
    digitalWrite(motorPinB1, LOW);
    digitalWrite(motorPinB2, LOW);
    }
}


void setup() {
  Serial.begin(115200);
  pinMode(motorPinA1, OUTPUT);
  pinMode(motorPinA2, OUTPUT);
  pinMode(motorPinB1, OUTPUT);
  pinMode(motorPinB2, OUTPUT);

   // init wifi 
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onDataReceived);
}

void loop() {
}
