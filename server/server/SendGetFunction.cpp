//#include "pch.h"
#include "Server.h"

bool Server::recvall(int index, char *data, int totalbytes)
{
	int bytesreceived = 0;
	while (bytesreceived < totalbytes)
	{
		int RetnCheck = recv(connections[index].socket, data + bytesreceived, totalbytes - bytesreceived, NULL);
		if (RetnCheck == SOCKET_ERROR)
			return false;
		bytesreceived += RetnCheck;
	}

	return true;
}

bool Server::sendall(int index, char *data, int totalbytes)
{
	int bytesent = 0;
	while (bytesent < totalbytes)
	{
		int RetnCheck = send(connections[index].socket, data + bytesent, totalbytes - bytesent, NULL);
		if (RetnCheck == SOCKET_ERROR)
			return false;

		bytesent += RetnCheck;
	}
	return true;
}


bool Server::Sendint32_t(int index, int32_t _int32_t)
{
	_int32_t = htonl(_int32_t);//convert from host byte order to network byte order
	if (!sendall(index, (char*)&_int32_t, sizeof(int32_t)))
		return false;
	return true;
}

bool Server::Getint32_t(int index, int32_t &_int32_t)
{
	if (!recvall(index, (char*)&_int32_t, sizeof(int32_t)))
		return false;
	_int32_t = ntohl(_int32_t);//from network to host byte order
	return true;
}

bool Server::SendPacketType(int index, PacketType _packettype)
{
	if (!Sendint32_t(index, (int32_t)_packettype))
		return false;
	return true;
}

bool Server::GetPacketType(int index, PacketType& _packettype)
{
	int pack_type;
	if (!Getint32_t(index, pack_type))
		return false;
	_packettype = (PacketType)pack_type;
	return true;
}

void Server::SendString(int index, std::string & _string)
{
	PS::ChatMessage message(_string);
	connections[index].p_o.Append_Pack(message.Conv_to_Pack());
}

bool Server::GetString(int index, std::string & _string)
{
	int32_t bufferlength; //Holds length of the message
	if (!Getint32_t(index, bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
	if (!recvall(index, buffer, bufferlength))
	{
		delete[] buffer;
		return false;
	}

	_string = buffer;
	delete[] buffer;
	return true;//Return true if we were successful in retrieving the string
}
