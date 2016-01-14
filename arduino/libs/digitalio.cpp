#include "protocol.h"
#include "digitalio.h"


int DigitalIo::execFun(Protocol protocol){
	String fun;
	fun = protocol.getFunction();
	if (String("doToggle") == fun){
		return _digitalOutToggle(protocol);
	}
	return DIO_OK;
}

int DigitalIo::_digitalOutToggle(Protocol protocol){
	int maxArgTry = 20;
	int pin;
	String arg;
	
	for(int i=0; i<maxArgTry; i++){
		arg = protocol.getArguments(i);
		if(arg.length()==0){
			break;
		}
		pin = arg.toInt();
		digitalWrite(pin, !digitalRead(pin));
		return DIO_OK;
	}
}
