#include "Client.h"

bool Client::recvall(char *data, int totalbytes)
{
	int bytesreceived = 0;
	while (bytesreceived < totalbytes)
	{
		int RetnCheck = recv(connection, data + bytesreceived, totalbytes - bytesreceived, NULL);
		if (RetnCheck == SOCKET_ERROR)
			return false;
		bytesreceived += RetnCheck;
	}

	return true;
}

bool Client::sendall(char *data, int totalbytes)
{
	int bytesent = 0;
	while (bytesent < totalbytes)
	{
		int RetnCheck = send(connection, data + bytesent, totalbytes - bytesent, NULL);
		if (RetnCheck == SOCKET_ERROR)
			return false;

		bytesent += RetnCheck;
	}
	return true;
}

bool Client::GetInt(int & _i)
{
	if (!recvall((char*)&_i, sizeof(int)))
		return false;
	return true;
}

bool Client::GetPacketType(Packet & pack_type)
{
	if (!recvall((char*)&pack_type, sizeof(Packet)))
		return false;
	return true;
}

bool Client::GetString(std::string & _string)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at

	if (!recvall(buffer, bufferlength))
	{
		delete[] buffer;
		return false;
	}

	_string = buffer;
	delete[] buffer;
	return true;//Return true if we were successful in retrieving the string	return false;
}

bool Client::SendInt(int _i)
{
	if (!sendall((char*)&_i, sizeof(int)))
		return false;
	return true;
}

bool Client::SendPacketType(Packet pack_type)
{
	if (!sendall((char*)&pack_type, sizeof(Packet)))
		return false;
	return true;
}
bool Client::SendString(std::string & _string)
{
	if (!SendPacketType(P_ChatMessage))
		return false; //Return false: Failed to send string
	int bufferlength = _string.size(); //Find string buffer length
	if (!SendInt(bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	if (!sendall((char*)_string.c_str(), bufferlength))
		return false;
	return true; //Return true: string successfully sent
}