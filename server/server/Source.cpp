//server
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<WinSock2.h>

SOCKET Connections[100];	//all connection list
int totalconnections = 0;	//total connection count

enum Packet
{
	P_ChatMessage,
	P_Test
};

bool SendInt(int index, int _i)
{
	int RetnCheck = send(Connections[index], (char*)&_i, sizeof(int), NULL); //send int: _i
	if (RetnCheck == SOCKET_ERROR) //If int failed to send due to connection issue
		return false; //Return false: Connection issue
	return true; //Return true: int successfully sent
}

bool GetInt(int index, int & _int)
{
	int RetnCheck = recv(Connections[index], (char*)&_int, sizeof(int), NULL); //receive integer
	if (RetnCheck == SOCKET_ERROR) //If there is a connection issue
		return false; //return false since we did not get the integer
	return true;//Return true if we were successful in retrieving the int
}

bool SendPacketType(int index, Packet _packettype)
{
	int RetnCheck = send(Connections[index], (char*)&_packettype, sizeof(Packet), NULL); //Send packet: _packettype
	if (RetnCheck == SOCKET_ERROR) //If packettype failed to send due to connection issue
		return false; //Return false: Connection issue
	return true; //Return true: int successfully sent
}

bool GetPacketType(int index, Packet & _packettype)
{
	int RetnCheck = recv(Connections[index], (char*)&_packettype, sizeof(Packet), NULL); //receive packet type (same as integer)
	if (RetnCheck == SOCKET_ERROR) //If there is a connection issue
		return false; //return false since we did not properly get the packet type
	return true;//Return true if we were successful in retrieving the packet type
}

bool SendString(int index, std::string & _string)
{
	if (!SendPacketType(index, P_ChatMessage)) //Send packet type: Chat Message, If sending packet type fails...
		return false; //Return false: Failed to send string
	int bufferlength = _string.size(); //Find string buffer length
	if (!SendInt(index, bufferlength)) //Send length of string buffer, If sending buffer length fails...
		return false; //Return false: Failed to send string buffer length
	int RetnCheck = send(Connections[index], _string.c_str(), bufferlength, NULL); //Send string buffer
	if (RetnCheck == SOCKET_ERROR) //If failed to send string buffer
		return false; //Return false: Failed to send string buffer
	return true; //Return true: string successfully sent
}

bool GetString(int index, std::string & _string)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(index, bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
	int RetnCheck = recv(Connections[index], buffer, bufferlength, NULL); //receive message and store the message in buffer array, set RetnCheck to be the value recv returns to see if there is an issue with the connection
	_string = buffer; //set string to received buffer message
	delete[] buffer; //Deallocate buffer memory (cleanup to prevent memory leak)
	if (RetnCheck == SOCKET_ERROR) //If connection is lost while getting message
		return false; //If there is an issue with connection, return false
	return true;//Return true if we were successful in retrieving the string
}

bool ProcessPacket(int index, Packet pack_type)
{
	switch (pack_type)
	{
	case P_ChatMessage://braces used so that variables can be declared
	{
		std::string Message; //string to store our message we received
		if (!GetString(index, Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false

		for (int i = 0; i < totalconnections; i++) //Next we need to send the message out to each user
		{
			if (i == index) //If connection is the user who sent the message...
				continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
			if (!SendString(i, Message)) //Send message to connection at index i, if message fails to be sent...
			{
				std::cout << "Failed to send message from client ID: " << index << " to client ID: " << i << std::endl;
			}
		}
		std::cout << "Processed chat message packet from user ID: " << index << std::endl;

		break;
	}
	default:
		std::cout << "Unknown packet received." << std::endl;
		break;
	}
	return true;//did not handle the proceess for not processing packet
}

void ClientHandlerThread(int index) //index = the index in the SOCKET Connections array
{
	Packet pack_type;
	while (true)
	{
		if (!GetPacketType(index, pack_type)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
		//Packet processing check is not implemented yet so it would not work
		if (!ProcessPacket(index, pack_type)) //If the packet is not properly processed
		{
			break; //break out of our client handler loop
		}

	}
	std::cout << "Lost connection to client ID:" << index << std::endl;
	closesocket(Connections[index]);
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

	//int msgBoxReturn = MessageBoxA(NULL, "YOU ARE GOING TO CREATE A CONNECTION!!\nMight make your device vulnerable to malwares", "Attention", MB_OKCANCEL | MB_ICONASTERISK);


	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"/*"172.17.37.17" /*its an example*/);  // the ip address of lan network
	addr.sin_port = htons(1111); //port 
	addr.sin_family = AF_INET;  //IPv4

	SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL);
	bind(slisten, (SOCKADDR*)&addr, sizeof(addr)); //bind adress to socket

	//tell socket to listen
	listen(slisten, SOMAXCONN);

	//socket to hold clients connection
	SOCKET newConn;
	int conn_count = 0;
	for (int i = 0; i < 10; i++)
	{
		newConn = accept(slisten, (SOCKADDR*)&addr, &addrlen);

		if (newConn == 0)
		{
			std::cout << "Failed to accept the client's connection." << std::endl;
		}
		else {
			std::cout << "client connected!!" << std::endl;

			Connections[i] = newConn;
			totalconnections++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL); //To Create Thread to handle this client.

			std::string MOTD = "MOTD: Welcome! This is the message of the day!.";
			SendString(i, MOTD);
		}
	}
	system("pause");


	exit(1);
}