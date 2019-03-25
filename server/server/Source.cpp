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

bool ProcessPacket(int index, Packet pack_type)
{
	switch (pack_type)
	{
	case P_ChatMessage://braces used so that variables can be declared
	{
		int bufferlength; //Length of the string
		//Logic for receiving a string

		int recvcheck = recv(Connections[index], (char*)&bufferlength, sizeof(int), NULL); //get buffer length
		char *buffer = new char[bufferlength]; //Allocate buffer
		recv(Connections[index], buffer, bufferlength, NULL); //get buffer message from client

		for (int i = 0; i < TotalConnections; i++) //For each client connection
		{
			if (i == index) //Don't send the chat message to the same user who sent it
			{
				continue; //Skip user
			}
				
			Packet chatmessagepacket = P_ChatMessage; //create chat message packet to be sent
			send(Connections[i], (char*)&chatmessagepacket, sizeof(Packet), NULL); //send chat message packet
			send(Connections[i], (char*)&bufferlength, sizeof(int), NULL);//send the buffer length to client at index i
			send(Connections[i], buffer, bufferlength, NULL);//send the chat message to client at index i
		}

		delete[] buffer; //Deallocate buffer to stop from leaking memory
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
	while (true)
	{
		//Getting Packet type
		Packet pack_type;
		recv(Connections[index], (char*)&pack_type, sizeof(Packet), NULL); //Receive packet type from client
		
		//Packet processing check is not implemented yet so it would not work
		if (!ProcessPacket(index, pack_type)) //If the packet is not properly processed
		{
			break; //break out of our client handler loop
		}
			
	}
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

	int msgBoxReturn = MessageBoxA(NULL, "YOU ARE GOING TO CREATE A CONNECTION!!\nMight make your device vulnerable to malwares", "Attention", MB_OKCANCEL | MB_ICONASTERISK);

	
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr(/*"127.0.0.1"*/"172.17.37.17" /*its an example*/);  // the ip address of lan network
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
				std::cout << "client connected!!" << endl;
	
				Connections[i] = newConn;
				totalconnections++;
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL); //To Create Thread to handle this client.
				
				std::string buff_test = "Message: Welcome! This is the message of the day!.";
				int size = buff_test.size(); //Get size of message in bytes and store it in int size
				Packet chatmessagepacket = P_ChatMessage; //Create packet type: Chat Message to be sent to the server
				send(Connections[i], (char*)&chatmessagepacket, sizeof(Packet), NULL); //Send packet type: Chat Message
				send(Connections[i], (char*)&size, sizeof(int), NULL); //send Size of message
				send(Connections[i], buff_test.c_str(), buff_test.size(), NULL); //send Message

				Packet testpacket = P_Test;
				send(Connections[i], (char*)&testpacket, sizeof(Packet), NULL); //Send test packet
				
			}
		}
		system("pause");
	
	
	exit(1);
}