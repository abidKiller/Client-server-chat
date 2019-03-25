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

bool ProcessPacket(Packet pack_type)
{
	switch (pack_type)
	{
	case P_ChatMessage:
	{
		int bufferlength; //length of the chat message
		recv(connection, (char*)&bufferlength, sizeof(int), NULL); //receive buffer
		char *buffer = new char[bufferlength + 1]; //Allocate buffer
		buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
		recv(connection, buffer, bufferlength, NULL);
		std::cout << buffer << std::endl; //print out buffer
		delete[] buffer; //Deallocate buffer
		break;
	}
	case P_Test:
		std::cout << "You have received the test packet!\nThis is the test packet!" << std::endl;
		break;
	default:
		std::cout << "Unknown packet: " << packettype << std::endl;
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
		recv(connection, (char*)&pack_type, sizeof(Packet), NULL); //Receive packet type from server

		if (!ProcessPacket(pack_type)) //If the packet is not properly processed, however not handled now
		{
			break; //break out of our client handler loop
		}
			
	}
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
		addr.sin_addr.s_addr = inet_addr("172.17.37.17"/*"192.168.0.11"*/ /*its an example*/);  // the ip address of lan network
		addr.sin_port = htons(1111); //port 
		addr.sin_family = AF_INET;  //IPv4

		connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(connection, (SOCKADDR*)&addr, addrlen) != 0)
		{
			MessageBoxA(NULL, "FAILED TO CONNECT", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		std::cout << "CONNECTED" << endl;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that receives data server sends.

		
		std::string userinput; //holds the user's chat message
		while (true)
		{
			std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
			int bufferlength = userinput.size(); //Find buffer length
			Packet chatmessagepacket = P_ChatMessage; //Create packet type: Chat Message to be sent to the server
			send(connection, (char*)&chatmessagepacket, sizeof(Packet), NULL); //Send packet type: Chat Message
			send(connection, (char*)&bufferlength, sizeof(int), NULL); //Send length of buffer
			send(connection, userinput.c_str(), bufferlength, NULL); //Send buffer
			Sleep(10);
		}
	
	
	system("pause");
	return 0;
}