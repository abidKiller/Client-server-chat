#include "pch.h"
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

bool Server::SendPacketType(int index, Packet _packettype)
{
	if (!Sendint32_t(index, _packettype))
		return false;
	return true;
}

bool Server::GetPacketType(int index, Packet &_packettype)
{
	int packettype;
	if (!Getint32_t(index, packettype))
		return false;
	_packettype = (Packet)packettype;
	return true;
}

bool Server::SendString(int index, std::string & _string)
{
	if (!SendPacketType(index, P_ChatMessage)) //Send packet type: Chat Message, If sending packet type fails...
		return false; //Return false: Failed to send string
	int32_t bufferlength = _string.size(); //Find string buffer length
	if (!Sendint32_t(index, bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	if (!sendall(index, (char*)_string.c_str(), bufferlength))
		return false;
	return true; //Return true: string successfully sent
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
