#include "EGTransfer.h"

//Captures address and size of struct
void EGTransfer::begin(uint8_t * ptr, uint8_t length, Stream *theStream){
	address = ptr;
	size = length;
	_stream = theStream;

	//dynamic creation of rx parsing buffer in RAM
	rx_buffer = (uint8_t*)malloc(size);
}

//Sends out struct in binary, with header, length info and checksum
void EGTransfer::sendData(){

	_stream->write(size);
	for (int i = 0; i<size; i++){
		_stream->write(*(address + i));
	}
}

boolean EGTransfer::receiveData(){
	//start off by looking for the header bytes. If they were already found in a previous call, skip it.
	if (rx_len == 0){
		//this size check may be redundant due to the size check below, but for now I'll leave it the way it is.
		if (_stream->available() >= 0){
			rx_len = _stream->read();
			//make sure the binary structs on both Arduinos are the same size.
			if (rx_len != size){
				rx_len = 0;
				return false;
			}
		}
	}

	//we get here if we already found the header bytes, the struct size matched what we know, and now we are byte aligned.
	if (_stream->available() >= 0){
		while (_stream->available() && rx_array_inx <= 8){
			rx_buffer[rx_array_inx++] = _stream->read();
		}
		if ( rx_array_inx == 8){
			//seem to have got whole message
			memcpy(address, rx_buffer, size);
			rx_len = 0;
			rx_array_inx = 0;
			return true;
		}
	}
	return false;
}
