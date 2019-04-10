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
	bool recvall(char *data, int totalbytes);
	bool Getint32_t(int32_t &_int32_t);
	bool GetPacketType(Packet & pack_type);
	bool GetString(std::string & _string);

	//senders
	bool sendall(char *data, int totalbytes);
	bool Sendint32_t(int32_t _int32_t);
	bool SendPacketType(Packet pack_type);

	//colection elements
	SOCKET connection;
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);


};

static Client *ptr;