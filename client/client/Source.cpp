//client
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<WinSock2.h>

SOCKET connection;

enum Packet
{
	P_ChatMessage,
	P_Test
};

bool SendInt(int _i)
{
	int RetnCheck = send(connection, (char*)&_i, sizeof(int), NULL);
	//function return
	if (RetnCheck == SOCKET_ERROR)				//If int failed to send due to connection issue
		return false;							//Return Connection issue
	return true;								// int successfully sent
}

bool GetInt(int & _i)
{
	int RetnCheck = recv(connection, (char*)&_i, sizeof(int), NULL);
	//receive integer
	if (RetnCheck == SOCKET_ERROR)		//If there is a connection issue
		return false;					//return false
	return true;						//Return true successful 
}

bool SendPacketType(Packet pack_type)
{
	int RetnCheck = send(connection, (char*)&pack_type, sizeof(Packet), NULL);
	//Send packet: _packettype
	if (RetnCheck == SOCKET_ERROR)			//If packettype failed to send due to connection issue
		return false;						//Return false: Connection issue
	return true;							//Return true: int successfully sent
}

bool GetPacketType(Packet & pack_type)
{
	int RetnCheck = recv(connection, (char*)&pack_type, sizeof(Packet), NULL);
	//receive packet type (same as integer)
	if (RetnCheck == SOCKET_ERROR)			//If connection issue
		return false;						//return false did not properly get the packet type
	return true;							//Return true successful retrieving the packet type
}

bool SendString(std::string & _string)
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

bool GetString(std::string & _string)
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
	return true;//Return true if we were successful in retrieving the string
}

bool ProcessPacket(Packet pack_type)
{
	switch (pack_type)
	{
	case P_ChatMessage:
	{
		std::string message;	//to store the message
		if (!GetString(message))	//get string with error check
			return false;
		std::cout << message << std::endl;
		break;
	}
	default:
		std::cout << "Unknown packet: " << pack_type << std::endl;
		break;
	}
	return true;//Does not handle if not processed
}

void ClientThread()
{
	//Handling packet types and their sizes rather than just sending char
	Packet pack_type;
	while (true)
	{
		//First get the packet type
		if (!GetPacketType(pack_type))
		{
			break;
		}
		if (!ProcessPacket(pack_type)) //If the packet is not properly processed, however not handled now
		{
			break; //break out of our client handler loop
		}
	}
	std::cout << "Connection to server lost" << std::endl;
	closesocket(connection);

}

//using namespace std;
int main()
{
	WSAData ws;
	WORD dll = MAKEWORD(2, 1);
	if (WSAStartup(dll, &ws) != 0)
	{
		MessageBoxA(NULL, "winsock Startup Failed", "error", MB_OK | MB_ICONERROR);
		exit(1);

	}


	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"/*"192.168.0.11"*/ /*its an example*/);  // the ip address of lan network
	addr.sin_port = htons(1111); //port 
	addr.sin_family = AF_INET;  //IPv4

	connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connection, (SOCKADDR*)&addr, addrlen) != 0)
	{
		MessageBoxA(NULL, "FAILED TO CONNECT", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	std::cout << "CONNECTED" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that receives data server sends.


	std::string userinput; //holds the user's chat message
	while (true)
	{
		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
		if (!SendString(userinput)) {		//send string to server
			break;
		}
		Sleep(10);
	}


	system("pause");
	return 0;
}