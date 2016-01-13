#include "protocol.h"


void Protocol::readData(){
	if(!_completed){
		_byteRead = Serial.read();
		//check header
		if (_byteRead == HEADER) {
			clearBuffer();
			_is_header = true;
		//no header
		} else {
			//store data if previous header
			if (_is_header) {
				//check end
				if (_byteRead == END){
					_completed = true;
				//store data
				} else {
					_buffer[_index] = _byteRead;
					_index++;
				}
			}
		}
	}	
};

void Protocol::clearBuffer(){
	_index = 0;
    _is_header = false;
    _completed = false;
}

bool Protocol::isCompleted(){
	return (bool)_completed;
}

String Protocol::getCompleteString(){
	String str = String("");
	char inChar;

	int i;
	if (_completed){
		for (i=0; i<=_index; i++){
			inChar = (char)_buffer[i];
			str = str + inChar;
		}
		return str;
	} else {
		return String("");
	}
}