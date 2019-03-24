//server
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<winSock2.h>

SOCKET Connections[100];	//all connection list
int totalconnections = 0;	//total connection count

void ClientHandlerThread(int index) //index = the index in the SOCKET Connections array
{
	char buffer[256]; //Buffer to receive and send out messages from/to the clients
	while (true)
	{
		recv(Connections[index], buffer, sizeof(buffer), NULL); //get message from client
		for (int i = 0; i < totalconnections; i++) //For each client connection
		{
			if (i == index) //Skip user
				continue; 
			send(Connections[i], buffer, sizeof(buffer), NULL); //send the chat message to other client
		}
	}
}

using namespace std;
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

	if (msgBoxReturn == IDOK) //creating socket
	{ 
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr(/*"127.0.0.1"*/"192.168.0.100" /*its an example*/);  // the ip address of lan network
		addr.sin_port = htons(1111); //port 
		addr.sin_family = AF_INET;  //IPv4

		SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL);
		bind(slisten, (SOCKADDR*)&addr, sizeof(addr)); //bind adress to socket

		//tell socket to listen
		listen(slisten, SOMAXCONN);

		//socket to hold clients connection
		SOCKET newConn;
		for (int i = 0; i < 10; i++) {
			newConn = accept(slisten, (SOCKADDR*)&addr, &addrlen);

			if (newConn == 0)
			{
				MessageBoxA(NULL, "Failed to accept client's connection ", "ERROR", MB_OK);
			}
			else {
				cout << "client connected!!" << endl;
				char msg[256] = "WELLCOME";
				send(newConn, msg, sizeof(msg), NULL);
				Connections[i] = newConn;
				totalconnections++;
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL); //To Create Thread to handle this client.
			}
		}
		system("pause");
	}
	
	exit(1);
}