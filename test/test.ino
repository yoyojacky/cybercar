#include <Arduino.h>

// define pinout

#define AIN1_PIN 4
#define AIN2_PIN 5
#define BIN1_PIN 7
#define BIN2_PIN 6

#define NSLEEP_PIN 0
#define NFAULT_PIN 1
#define interval  5000

// control fucntion
void motorControl(uint8_t motor, uint8_t action) {
  switch (motor) {
	case 1: // motor 1
           switch (action) {
		case 0: //正转
			digitalWrite(AIN1_PIN, HIGH);	
			digitalWrite(AIN2_PIN, LOW);	
			break;
		case 1: //反转
			digitalWrite(AIN1_PIN, LOW);	
			digitalWrite(AIN2_PIN, HIGH);	
			break;
		case 3: //制动
			digitalWrite(AIN1_PIN, HIGH);	
			digitalWrite(AIN2_PIN, HIGH);	
			break;
		}
	       break;
	case 2: // 电机2 
	  switch (action) {
		case 0: //正转
			digitalWrite(BIN1_PIN, HIGH);	
			digitalWrite(BIN2_PIN, LOW);	
			break;
		case 1: //反转
			digitalWrite(BIN1_PIN, LOW);	
			digitalWrite(BIN2_PIN, HIGH);	
			break;
		case 3: //制动
			digitalWrite(BIN1_PIN, HIGH);	
			digitalWrite(BIN2_PIN, HIGH);	
			break;
		}
	   break;
	}
}




void setup() {
   Serial.begin(9600);
  // init 
   pinMode(AIN1_PIN, OUTPUT);
   pinMode(AIN2_PIN, OUTPUT);
   pinMode(BIN1_PIN, OUTPUT);
   pinMode(BIN2_PIN, OUTPUT);

   pinMode(NSLEEP_PIN, OUTPUT);
   pinMode(NFAULT_PIN, INPUT);

   // Start init 
   Serial.println("Start engine...");
   digitalWrite(NSLEEP_PIN, HIGH);
   Serial.print("NSLEEP_PIN's Status:");
   Serial.println(NSLEEP_PIN);
}

void loop() {

	if (digitalRead(NFAULT_PIN) == LOW) {
		Serial.println("Motor driver fault detected!");
	   digitalWrite(NSLEEP_PIN, LOW);
           delay(100);
	   digitalWrite(NSLEEP_PIN, HIGH);
	}

    // motor 1 control 
   Serial.println("No.1 forward");
   motorControl(1,0); 
   delay(interval);
   Serial.println("No.1 backforward");
   motorControl(1, 1);
   delay(interval);
   Serial.println("No.1 stop");
   motorControl(1, 2);
   delay(interval);

   Serial.println("No.2 forward");
   motorControl(2,0); 
   delay(interval);
   Serial.println("No.2 backforward");
   motorControl(2, 1);
   delay(interval);
   Serial.println("No.2 stop");
   motorControl(2, 2);
   delay(interval);
    
   Serial.println("No.1 and No.2 forward");
   motorControl(1,0); 
   motorControl(2,0); 
   delay(interval);

   Serial.println("No.1 and No.2 backforward");
   motorControl(1, 1);
   motorControl(2, 1);
   delay(interval);

   Serial.println("No.1 and No.2 stop");
   motorControl(1, 2);
   motorControl(2, 2);
   delay(interval);
}
