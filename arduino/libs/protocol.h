#include "Arduino.h"

#ifndef protocol_h
#define protocol_h


#define MAX_LENGHT	50 
#define HEADER '^'
#define END '*'
#define ID_SEPARATOR1 '<'
#define ID_SEPARATOR2 '>'
#define DATA_SERPARATOR ','
#define REQUEST_SEPARATOR '-'

/*
^<{ID}>{FUN},{DATA}-{REQUEST}*

^<1234>don,13-0101* // Digital output switch on: pin 13
^<1234>rst-123*  // Reset

,{DATA} is optional
*/

class Protocol
{
  public:
  //methods
  void readData();
  void clearBuffer();

  bool isCompleted();

  String getCompleteString();
  String getId();
  String getGetRequestId();
  String getCmd();
  void printData();
  //attributes
  
  private:
    //Attributes
    byte _byteRead;
    byte _buffer[MAX_LENGHT];
    int _index = 0;
    bool _is_header = false;
  	bool _completed = false;
  	String _completeString;
  	String _id;
  	String _cmd;
  	String _fun;
    String _idRequest;
   //methods
};

#endif

