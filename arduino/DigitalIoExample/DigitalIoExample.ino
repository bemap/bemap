#include "protocol.h"
#include "digitalio.h"
#include "bemap.h"


#define LED 13
#define ID "1234"

//comand: ^<1234>doToggle,13-0101*


byte byteRead;
Protocol protocol;

DigitalIo digIo;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
	if (Serial.available()) {
		protocol.readData();
		if (protocol.isCompleted()){
			if(protocol.getId() == ID){
				digIo.execFun(protocol);
			}
			protocol.printData();
			protocol.clearBuffer();
		}
	}
}