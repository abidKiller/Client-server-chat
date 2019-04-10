#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include <iostream>
#include <WinSock2.h>
#include <string>



enum Packet
{
	P_ChatMessage,
	P_Test
};

class Server {
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

private:

	bool sendall(int index, char *data, int totalbytes);
	bool recvall(int index, char *data, int totalbytes);

	bool ProcessPacket(int index, Packet pack_type);
	static void ClientHandlerThread(int index);

	//int getter sender
	bool Sendint32_t(int index, int32_t _int32_t);
	bool Getint32_t(int index, int32_t & _int32_t);

	//packet getter sender
	bool SendPacketType(int index, Packet pack_type);
	bool GetPacketType(int index, Packet & pack_type);

	//string getter sender
	bool SendString(int index, std::string & _string);
	bool GetString(int index, std::string & _string);

private:
	//socket address
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	//listener socket
	SOCKET slisten;
	//socket
	SOCKET connections[100];	//all connection list
	int totalconnections = 0;	//total connection count
};

static Server *sptr;//server pointer