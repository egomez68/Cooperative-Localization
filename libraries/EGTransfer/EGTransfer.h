// EGTransfer Arduino Library

#ifndef EGTransfer_h
#define EGTransfer_h
#define details(name) (byte*)&name,sizeof(name)
#include "Arduino.h"

class EGTransfer {
public:
	void begin(uint8_t *, uint8_t, Stream *theStream);
	void sendData();
	boolean receiveData();
private:
	Stream *_stream;
	uint8_t * address;  //address of struct
	uint8_t size;       //size of struct
	uint8_t * rx_buffer; //address for temporary storage and parsing buffer
	uint8_t rx_array_inx;  //index for RX parsing buffer
	uint8_t rx_len;		//RX packet length according to the packet
};
#endif
