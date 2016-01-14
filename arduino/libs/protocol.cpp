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
    _completeString = String("");
    _id = String("");
    _idRequest =  String("");
    _cmd =  String("");
}

bool Protocol::isCompleted(){
	return (bool)_completed;
}

String Protocol::getCompleteString(){
	String str = String("");
	int i;
	if (!_completed){
		return String("");
	}
	// if previous value
	if(_completeString.length() > 0){
	 	return _completeString;
	 }
	for (i=0; i<=_index; i++){
		str = str + (char)_buffer[i];
	}
	_completeString = str;
	return str;
	
}

String Protocol::getId(){
	String completeStr;
	String response = String("");
	int i;
	int len;
	bool isIdSeparator1 = false;
	

	if (!_completed){
		return String("");
	}
	// if previous value
	if(_id.length() > 0){
	 	return _id;
	 }

	//try to get complete string
	if(_completeString.length() == 0){
		getCompleteString();
		//there is no valid data
		if(_completeString.length() == 0){
			return String("");	
		}
	}

	len = _completeString.length();

	for(i=0; i<len; i++){
		if (ID_SEPARATOR1 == (char)_completeString[i]){
			isIdSeparator1 = true;
			continue;
		}
		if(isIdSeparator1){
			if (ID_SEPARATOR2 == (char)_completeString[i]){
				_id = response;
				return response;
			} else {
				response = response + _completeString[i];
			}
		}
	}
	return String("");
}



String Protocol::getGetRequestId(){
	String response = String("");
	bool isRequestSeparator = false;
	int i;
	int len;


	//try to get complete string
	if(_completeString.length() == 0){
		getCompleteString();
		//there is no valid data
		if(_completeString.length() == 0){
			return String("");	
		}
	}
	for(i=0; i < _completeString.length(); i++){
		if (REQUEST_SEPARATOR == (char)_completeString[i]){
			isRequestSeparator = true;
			continue;
		}
		if (isRequestSeparator){
			response = response + (char)_completeString[i];
		}
	}
	if (isRequestSeparator){
		_idRequest = response;
		return response;
	} else {
		return String("");
	}
}




String Protocol::getCmd(){
	String response;
	String completeStr;
	int i;
	int len;
	int startCmdIndex;
	int startRequest;

	
	//try to get complete string
	if(_completeString.length() == 0){
		getCompleteString();
		//there is no valid data
		if(_completeString.length() == 0){
			return String("");	
		}
	}


	//try to get id
	if(_id.length() == 0){
		getId();
		//there is no valid id
		if(_id.length() == 0){
			return String("");	
		}
	}
	//try to get _idRequest
	if(_idRequest.length() == 0){
		getGetRequestId();
		//there is no valid data
		if(_idRequest.length() == 0){
			return String("");	
		}
	}
	
	//ID_SEPARATOR1 + ID + ID_SERPARATOR2
	startCmdIndex = 1 + _id.length() + 1; 
	len = _completeString.length();	
	startRequest = (len - (1 + _idRequest.length()) ) - 1	;
	if (len<=0){
		return String("");
	}
	for(i=startCmdIndex; i<=startRequest; i++){
		response = response + _completeString[i];
	}
	_cmd = response;
	return response;
}



void Protocol::printData(){
	Serial.print("complete command: ");
    Serial.println(getCompleteString());
    Serial.print("id: ");
    Serial.println(getId());
    Serial.print("request: ");
    Serial.println(getGetRequestId());
    Serial.print("cmd: ");
    Serial.println(getCmd());

}
