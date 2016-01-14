#include "Arduino.h"
#include "protocol.h"

#ifndef digitalio_h
#define digitalio_h
#define DIO_ERROR -1
#define DIO_OK 0
#define DIO_LOW 10
#define DIO_HIGH 20

class DigitalIo
{
	public:
	//methods
	int execFun(Protocol protocol);
	
	//attributes

	private:
	//Attributes
	//methods
	int _digitalOutToggle(Protocol protocol);
};

#endif

