#pragma once
#include "PacketType.h"
class Packet
{
public:
	Packet();
	Packet(char * buffer, int size); //Will use existing allocated buffer and create packet from it
	Packet(const Packet & p); //Will allocate new buffer but copy buffer from packet argument
	Packet(PacketType p); //Used for when sending a packet that only contains a packet type (Ex. End of File Packet)
	int size;
	char * buffer;
};