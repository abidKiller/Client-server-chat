#include "Server.h"

bool Server::recvall(int index, char *data, int totalbytes)
{
	int bytesreceived = 0;
	while (bytesreceived < totalbytes)
	{
		int RetnCheck = recv(connections[index], data + bytesreceived, totalbytes - bytesreceived, NULL);
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
		int RetnCheck = send(connections[index], data + bytesent, totalbytes - bytesent, NULL);
		if (RetnCheck == SOCKET_ERROR)
			return false;

		bytesent += RetnCheck;
	}
	return true;
}


bool Server::SendInt(int index, int _i)
{
	if (!sendall(index, (char*)&_i, sizeof(int)))
		return false;
	return true;//Return true: int successfully sent
}

bool Server::GetInt(int index, int & _int)
{
	if (!recvall(index, (char*)&_int, sizeof(int)))
		return false;
	return true;//Return true if we were successful in retrieving the int
}

bool Server::SendPacketType(int index, Packet pack_type)
{
	f(!sendall(index, (char*)&pack_type, sizeof(Packet)))
		return false;
	return true; //Return true: int successfully sent
}

bool Server::GetPacketType(int index, Packet & pack_type)
{
	if (!recvall(index, (char*)&pack_type, sizeof(Packet)))
		return false;
	return true;//Return true if we were successful in retrieving the packet type
}

bool Server::SendString(int index, std::string & _string)
{
	if (!SendPacketType(index, P_ChatMessage)) //Send packet type: Chat Message, If sending packet type fails...
		return false; //Return false: Failed to send string
	int bufferlength = _string.size(); //Find string buffer length
	if (!SendInt(index, bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	if (!sendall(index, (char*)_string.c_str(), bufferlength))
		return false;
	return true; //Return true: string successfully sent
}

bool Server::GetString(int index, std::string & _string)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(index, bufferlength)) //Get length of buffer and store it in variable: bufferlength
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
