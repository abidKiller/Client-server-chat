#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<WinSock2.h>



enum Packet
{
	P_ChatMessage,
	P_Test
};

class Client 
{
public:
	
	Client(std::string IP, int port);
	bool ConnectServer();
	bool DisconnectServer();
	
	//string setter for user input
	bool SendString(std::string & _string);

private:
	
	bool ProcessPacket(Packet pack_type);
	static void ClientThread();
	
	//getters
	bool GetInt(int & _i);
	bool GetPacketType(Packet & pack_type);
	bool GetString(std::string & _string);
	
	//senders
	bool SendInt(int _i);
	bool SendPacketType(Packet pack_type);
	
	//colection elements
	SOCKET connection;
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);


};

static Client *ptr; 