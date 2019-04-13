#pragma once
#include "PacketType.h"
#include "Packet.h"
#include <string>

namespace PS //Packet_Struct Namespace
{
	class ChatMessage
	{
	public:
		ChatMessage(std::string);
		Packet Conv_to_Pack(); //Converts ChatMessage to packet
	private:
		std::string message;
	};
}

