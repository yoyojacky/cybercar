#include <esp_now.h>
#include <WiFi.h>

// 定义电位计连接的引脚
const int potPin = 0;

// 定义接收端的mac地址
uint8_t receiverMac[] = {};

// 数据结构
struct Data {
  int potValue;
}; 

// 发送数据的函数
void sendPotValue() {
	Data data;
	data.potValue = analogRead(potPin); //读取电位计的值
	esp_err_t result = esp_now_send(receiverMac, (uint8_t*)&data, sizeof(data));
    if(result == ESP_OK) {
	Serial.println("Send data successfully");
	} else {
	Serial.println("Error Sending data");
	}
}


void setup() {
	Serial.begin(115200);
	pinMode(potPin, INPUT);
	
	// init wifi 
	WiFi.mode(WIFI_STA);
	esp_now_init();
	esp_now_peer_info_t peerInfo;
	memcpy(peerInfo.peer_addr, receiverMac, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;
	esp_now_add_peer(&peerInfo);
}

void loop() {
	sendPotValue();
	delay(2);
}

