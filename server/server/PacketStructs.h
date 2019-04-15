#pragma once
#include "PacketType.h"
#include "Packet.h"
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
}