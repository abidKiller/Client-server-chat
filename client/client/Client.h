#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<WinSock2.h>
#include "FileTransferData.h"
#include "PacketType.h"

using namespace std;



class Client
{
public:

	Client(std::string IP, int port);
	bool ConnectServer();
	bool DisconnectServer();

	//string setter for user input
	bool SendString(string & _string, bool IncludePacketType = true);
	bool RequestFile(string FileName);

private:

	bool ProcessPacket(PacketType pack_type);
	static void ClientThread();

	//getters
	bool recvall(char *data, int totalbytes);
	bool Getint32_t(int32_t &_int32_t);
	bool GetPacketType(PacketType& pack_type);
	bool GetString(string & _string);

	//senders
	bool sendall(char *data, int totalbytes);
	bool Sendint32_t(int32_t _int32_t);
	bool SendPacketType(PacketType pack_type);

	//colection elements
	SOCKET connection;
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	FileTransferData file;


};

static Client *ptr;