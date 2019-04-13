#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib") //Required for linking WinSock
#include <WinSock2.h> 
#include <string> 
#include <iostream> 
#include "FileTransferData.h"
#include "Packet_Org.h"
#include "Packet_Struct.h"

using namespace std;


struct Connection
{
	SOCKET socket;
	FileTransferData file;
	Packet_Org p_o;
};

class Server 
{
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

private:

	bool sendall(int index, char *data, int totalbytes);
	bool recvall(int index, char *data, int totalbytes);

	bool ProcessPacket(int index, PacketType pack_type);
	bool HandleSendFile(int index);
	

	//int getter sender with 32bit int
	bool Sendint32_t(int index, int32_t _int32_t);
	bool Getint32_t(int index, int32_t & _int32_t);

	//packet getter sender
	bool SendPacketType(int index, PacketType pack_type);
	bool GetPacketType(int index, PacketType& pack_type);

	//string getter sender
	void SendString(int index, std::string & _string);
	bool GetString(int index, std::string & _string);

	static void ClientHandlerThread(int index); 
	static void PacketSenderThread();	
	

private:
	//socket address
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	//listener socket
	SOCKET slisten;
	//socket
	Connection connections[100];	//all connection list
	int totalconnections = 0;	//total connection count
};

static Server *sptr;//server pointer