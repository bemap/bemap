#include "Arduino.h"

#ifndef protocol_h
#define protocol_h


#define MAX_LENGHT	50 
#define HEADER '^'
#define END '*'
#define SEPARATOR ','

class Protocol
{
  public:
  //methods
  void readData();
  void clearBuffer();
  String getCompleteString();
  bool isCompleted();

  //attributes
  
  private:
    //Attributes
    byte _byteRead;
    byte _buffer[MAX_LENGHT];
    int _index = 0;
    bool _is_header = false;
  	bool _completed = false;
   //methods
};

#endif

