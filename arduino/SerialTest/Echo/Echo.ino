#include "protocol.h"
#include "bemap.h"

byte byteRead;
Protocol protocol;

void setup() {                
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    protocol.readData();
    if (protocol.isCompleted()){
      Serial.println(protocol.getCompleteString());
      protocol.clearBuffer();
    }
  }
}