//#include "pch.h"
#include "Client.h"

Client::Client(std::string IP, int port)
{
	WSAData ws;
	WORD dll = MAKEWORD(2, 1);
	if (WSAStartup(dll, &ws) != 0)
	{
		MessageBoxA(NULL, "winsock Startup Failed", "error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(IP.c_str());  // the ip address
	addr.sin_port = htons(port); //port 
	addr.sin_family = AF_INET;  //IPv4 socket

	ptr = this;
}

bool Client::ConnectServer()
{
	connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connection, (SOCKADDR*)&addr, addrlen) != 0)
	{
		MessageBoxA(NULL, "FAILED TO CONNECT", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	std::cout << "Connected!" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that receives data server sends.

	return true;
}

bool Client::DisconnectServer()
{
	if (closesocket(connection) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK) //If socket error is that operation is not performed on a socket (This happens when the socket has already been closed)
			return true; //return true since connection has already been closed

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}


bool Client::ProcessPacket(PacketType pack_type)
{
	switch (pack_type)
	{
	case PacketType::ChatMessage:
	{
		std::string message;	//to store the message
		if (!GetString(message))	//get string with error check
			return false;
		std::cout << message << std::endl;
		break;
	}
	case PacketType::FileTransferByteBuffer://if we're receiving byte buffer from server
	{
		int32_t buffersize;
		if (!Getint32_t(buffersize))
			return false;

		if (!recvall(file.buffer, buffersize))//receive data and store to buffer of structure
			return false;
		file.outfileStream.write(file.buffer, buffersize);
		file.byteswritten += buffersize;

		cout << "received byte buffer for file transfer of size: " << buffersize << endl;

		//send packet to request next byte buffer from server
		if (!SendPacketType(PacketType::FileTransferRequestNextBuffer)) //send PacketType type to request next byte buffer (if one exists)
			return false;
		break;
	}
	case PacketType::FileTransfer_EndOfFile:
	{
		cout << "file transfer completed. file received." << endl;
		cout << "file name: " << file.fileName << endl;
		cout << "file size (bytes): " << file.byteswritten << endl;
		file.byteswritten = 0;
		file.outfileStream.close();
		break;
	}
	default:
		std::cout << "Unknown packet: " << (int32_t)pack_type << std::endl;
		break;
	}
	return true;//Does not handle if not processed

}

void Client::ClientThread()
{
	//Handling packet types and their sizes rather than just sending char
	PacketType pack_type;
	while (true)
	{
		//First get the packet type
		if (!ptr->GetPacketType(pack_type))
		{
			break;
		}
		if (!ptr->ProcessPacket(pack_type)) //If the packet is not properly processed, however not handled now
		{
			break; //break out of our client handler loop
		}
	}
	std::cout << "Connection to server lost" << std::endl;
	if (ptr->DisconnectServer()) //Try to close socket connection..., If connection socket was closed properly
	{
		std::cout << "Socket to the server was closed fgffj successfuly." << std::endl;
	}
	else //If connection socket was not closed properly for some reason from our function
	{
		std::cout << "Socket was not able to be closed." << std::endl;
	}

}

bool Client::RequestFile(std::string FileName)
{
	//open file in binary to outfilestream
	file.outfileStream.open(FileName, ios::binary);
	file.fileName = FileName;
	file.byteswritten = 0;

	//make sure file opens successfully
	if (!file.outfileStream.is_open())
	{
		cout << "error: function(client::RequestFile) - unable to open file: " << FileName << " for writing." << endl;
		return false;
	}

	cout << "requesting file from server: " << FileName << endl;

	//send packet to server to request file
	if (!SendPacketType(PacketType::FileTransferRequestFile))
		return false;

	//send name of file to server
	if (!SendString(FileName, false))
		return false;

	return true;
}


