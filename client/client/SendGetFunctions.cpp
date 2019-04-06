#include "Client.h"


bool Client::GetInt(int & _i)
{
	int RetnCheck = recv(connection, (char*)&_i, sizeof(int), NULL);
	//receive integer
	if (RetnCheck == SOCKET_ERROR)		//If there is a connection issue
		return false;					//return false
	return true;
}

bool Client::GetPacketType(Packet & pack_type)
{
	int RetnCheck = recv(connection, (char*)&pack_type, sizeof(Packet), NULL);
	//receive packet type (same as integer)
	if (RetnCheck == SOCKET_ERROR)			//If connection issue
		return false;						//return false did not properly get the packet type
	return true;
}

bool Client::GetString(std::string & _string)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
	int RetnCheck = recv(connection, buffer, bufferlength, NULL); //receive message and store the message in buffer array, set RetnCheck to be the value recv returns to see if there is an issue with the connection
	_string = buffer; //set string to received buffer message
	delete[] buffer; //Deallocate buffer memory (cleanup to prevent memory leak)
	if (RetnCheck == SOCKET_ERROR) //If connection is lost while getting message
		return false; //If there is an issue with connection, return false
	return true;//Return true if we were successful in retrieving the string	return false;
}

bool Client::SendInt(int _i)
{
	int RetnCheck = send(connection, (char*)&_i, sizeof(int), NULL);
	//function return
	if (RetnCheck == SOCKET_ERROR)				//If int failed to send due to connection issue
		return false;							//Return Connection issue
	return true;
}

bool Client::SendPacketType(Packet pack_type)
{
	int RetnCheck = send(connection, (char*)&pack_type, sizeof(Packet), NULL);
	//Send packet: _packettype
	if (RetnCheck == SOCKET_ERROR)			//If packettype failed to send due to connection issue
		return false;						//Return false: Connection issue
	return true;
}
bool Client::SendString(std::string & _string)
{
	if (!SendPacketType(P_ChatMessage))
		return false; //Return false: Failed to send string
	int bufferlength = _string.size(); //Find string buffer length
	if (!SendInt(bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	int RetnCheck = send(connection, _string.c_str(), bufferlength, NULL); //Send string buffer
	if (RetnCheck == SOCKET_ERROR) //If failed to send string buffer
		return false; //Return false: Failed to send string buffer
	return true; //Return true: string successfully sent
}