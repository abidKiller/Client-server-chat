#pragma once
#include "Packet.h"
#include <queue>
#include <mutex>

class Packet_Org
{
private:
	std::queue<Packet> que_packet;
	std::mutex mutex_packet;
public:
	bool HasPendingPacket();
	void Append_Pack(Packet p);
	Packet Retrieve_Pack();
};
