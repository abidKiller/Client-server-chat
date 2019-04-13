#include "Packet_Org.h"

bool Packet_Org::HasPendingPacket()
{
	return (que_packet.size() > 0); //returns true if size > 0 false otherwise
}

void Packet_Org::Append_Pack(Packet p)
{
	std::lock_guard<std::mutex> lock(mutex_packet); //lock mutex so two threads dont access data at same time
	que_packet.push(p); //Add packet to queue
}

Packet Packet_Org::Retrieve_Pack()
{
	std::lock_guard<std::mutex> lock(mutex_packet);
	Packet p = que_packet.front(); //Get packet from front of queue
	que_packet.pop(); //Remove packet from front of queue
	return p; //Return packet that was removed from the queue
}