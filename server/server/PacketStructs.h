#pragma once
#include "PacketType.h"
#include "Packet.h"
#include "FileTransferData.h"
#include <string>

namespace PS //Packet Structures Namespace
{
	class ChatMessage
	{
	public:
		ChatMessage(std::string);
		Packet toPacket(); //Converts ChatMessage to packet
	private:
		std::string message;
	};
	class FileDataBuffer //Used when sending a file
	{
	public:
		Packet toPacket(); //Converts FileDataBuffer to Packet so that it can be appended to packet manager
		char databuffer[FileTransferData::buffersize]; //buffer of data to be sent
		int size; //size of data buffer
	};
}