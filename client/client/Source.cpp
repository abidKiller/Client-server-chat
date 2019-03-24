#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<winSock2.h>

SOCKET connection;
void ClientThread()
{
	char message[256]; //buffer to hold messages
	while (true)
	{
		recv(connection, message, sizeof(message), NULL); //receive buffer
		std::cout << message << std::endl; //print buffer
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
		addr.sin_addr.s_addr = inet_addr("192.168.0.100"/*"192.168.0.11"*/ /*its an example*/);  // the ip address of lan network
		addr.sin_port = htons(1111); //port 
		addr.sin_family = AF_INET;  //IPv4

		connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(connection, (SOCKADDR*)&addr, addrlen) != 0)
		{
			MessageBoxA(NULL, "FAILED TO CONNECT", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		cout << "CONNECTED" << endl;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that receives data server sends.

		
		char message[256];
		while (true)
		{
			std::cin.getline(message, sizeof(message)); //Get line if user presses enter and fill the buffer
			send(connection, message, sizeof(message), NULL); //Send buffer
			Sleep(10);
		}
	
	}
	system("pause");
	return 0;
}