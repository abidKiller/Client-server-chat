//server
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<winSock2.h>

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
		
		newConn = accept(slisten, (SOCKADDR*)&addr,&addrlen);

		if (newConn == 0)
		{
			MessageBoxA(NULL, "Failed to accept client's connection ", "ERROR", MB_OK);
		}
		else {
			cout << "client connected!!" << endl;
			char msg[256] = "WELLCOME";
			send(newConn, msg, sizeof(msg), NULL);
		}
		system("pause");
	}
	
	exit(1);
}