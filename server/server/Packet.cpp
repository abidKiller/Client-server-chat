#include "Packet.h"
#include <Windows.h>
#include <stdint.h> //Required to use int32_t

Packet::Packet()
{

}

Packet::Packet(char * _buffer, int _size)
{
	buffer = _buffer;
	size = _size;
}

Packet::Packet(const Packet & p) //Allocate new block for buffer
{
	size = p.size;
	buffer = new char[size];
	memcpy(buffer, p.buffer, size);
}

Packet::Packet(PacketType p) //Used for creating a packet that only contains a packet type to be sent
{
	buffer = new char[sizeof(int32_t)]; //Create buffer to store packet type data
	int32_t packettype = (int32_t)p; //store packet type in a 32 bit integer
	packettype = htonl(packettype); //Convert from host to network byte order
	memcpy(buffer, &packettype, sizeof(int32_t)); //Copy from 32 bit integer to buffer
	size = sizeof(int32_t); //Set size to size of 32 bit integer
}
