//#include "pch.h"
#include "Server.h"

Server::Server(int PORT, bool BroadcastPublically)//false if server not in same router // true if in same computer 
{
	WSAData wsData;
	WORD dll = MAKEWORD(2, 1);
	if (WSAStartup(dll, &wsData) != 0)
	{
		MessageBoxA(NULL, "winsock Startup Failed", "error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	//int msgBoxReturn = MessageBoxA(NULL, "YOU ARE GOING TO CREATE A CONNECTION!!\nMight make your device vulnerable to malwares", "Attention", MB_OKCANCEL | MB_ICONASTERISK);


	if (BroadcastPublically) //If server is open to public
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else //If server is only for our router
		addr.sin_addr.s_addr = inet_addr("192.168.10.101"); //Broadcast locally

	addr.sin_port = htons(PORT); //port 
	addr.sin_family = AF_INET;  //IPv4

	slisten = socket(AF_INET, SOCK_STREAM, NULL);


	if (bind(slisten, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) //Bind the address to the socket, if we fail to bind the address..
	{
		std::string ErrorMsg = "Failed to bind the address to our listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	if (listen(slisten, SOMAXCONN) == SOCKET_ERROR) //Places slisten socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max connections, if we fail to listen on listening socket...
	{
		std::string ErrorMsg = "Failed to listen on listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	sptr = this;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PacketSenderThread, NULL, NULL, NULL); //Create thread that will manage all outgoing packets
}

bool Server::ListenForNewConnection()
{
	SOCKET newConn = accept(slisten, (SOCKADDR*)& addr, &addrlen);;
	
	if (newConn == 0)
	{
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}
	else 
	{
		std::cout << "client connected!!" << std::endl;
		connections[totalconnections].socket = newConn;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(totalconnections), NULL, NULL); //To Create Thread to handle this client.
		//std::string MOTD = "MOTD: Welcome! This is hjksfvservghgrvhw the message of the day!.";
		//SendString(totalconnections, MOTD);
		totalconnections++;
		return true;
	}
}

bool Server::ProcessPacket(int index, PacketType pack_type)
{
	switch (pack_type)
	{
	case PacketType::ChatMessage://braces used so that variables can be declared
	{
		std::string Message; //string to store our message we received
		if (!GetString(index, Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false

		for (int i = 0; i < totalconnections; i++) //Next we need to send the message out to each user
		{
			if (i == index) //If connection is the user who sent the message...
				continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
			SendString(i, Message); //Send message to connection at index i, if message fails to be sent...
			
		}
		std::cout << "Processed chat message packet from user index: " << index << std::endl;

		break;
	}
	case PacketType::FileTransferRequestFile: //when client request a file from server
	{
		string FileName;
		if (!GetString(index, FileName))
			return false;
		connections[index].file.infileStream.open(FileName, ios::binary | ios::ate);
		if (!connections[index].file.infileStream.is_open())
		{
			std::cout << "client: " << index << " requested file: " << FileName << " , but that file doesn't exist." << endl;
			std::string errmsg = "requested file: " + FileName + " doesn't exist or not found.";
			SendString(index, errmsg); //send error msg to clients
			return true;
		}

		connections[index].file.fileName = FileName;
		connections[index].file.fileSize = connections[index].file.infileStream.tellg(); //Get file size
		connections[index].file.infileStream.seekg(0);
		connections[index].file.fileOffset = 0;

		if (!HandleSendFile(index))//attempt to send byte buffer from file.
			return false;

		break;
	}
	case PacketType::FileTransferRequestNextBuffer: //when client requests next buffer for current file
	{
		if (!HandleSendFile(index))//attempt to send byte buffer from file.
			return false;
		break;
	}
	default:
		std::cout << "unrecognized packet: " << (int32_t)pack_type << std::endl;
		break;
	}
	return true;//did not handle the proceess for not processing packet
}

bool Server::HandleSendFile(int index)
{
	if (connections[index].file.fileOffset >= connections[index].file.fileSize)
		return true;
	if (!SendPacketType(index, PacketType::FileTransferByteBuffer))//send packet type for file transfer byte buffer
		return false;

	connections[index].file.remainingBytes = connections[index].file.fileSize - connections[index].file.fileOffset;
	if (connections[index].file.remainingBytes > connections[index].file.buffersize)
	{
		connections[index].file.infileStream.read(connections[index].file.buffer, connections[index].file.buffersize);
		if (!Sendint32_t(index, connections[index].file.buffersize))//send int of buffersize
			return false;
		if (!sendall(index, connections[index].file.buffer, connections[index].file.buffersize))
			return false;
		connections[index].file.fileOffset += connections[index].file.buffersize;
	}
	else
	{
		connections[index].file.infileStream.read(connections[index].file.buffer, connections[index].file.remainingBytes);
		if (!Sendint32_t(index, connections[index].file.remainingBytes))//send int of buffersize
			return false;
		if (!sendall(index, connections[index].file.buffer, connections[index].file.remainingBytes))
			return false;
		connections[index].file.fileOffset += connections[index].file.remainingBytes;
	}

	if (connections[index].file.fileOffset == connections[index].file.fileSize)
	{
		if (!SendPacketType(index, PacketType::FileTransfer_EndOfFile))
			return false;
		std::cout << endl << "file sent: " << connections[index].file.fileName << std::endl;
		std::cout << "file size(bytes): " << connections[index].file.fileSize << std::endl << std::endl;
	}

	return true;
}


void Server::ClientHandlerThread(int index)
{
	PacketType pack_type;
	while (true)
	{
		if (!sptr->GetPacketType(index, pack_type)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
		//Packet processing check is not implemented yet so it would not work
		if (!sptr->ProcessPacket(index, pack_type)) //If the packet is not properly processed
		{
			break; //break out of our client handler loop
		}

	}
	std::cout << "Lost connection to client index:" << index << std::endl;
	closesocket(sptr->connections[index].socket);
	return;
}

void Server::PacketSenderThread() //Thread for all outgoing packets
{
	while (true)
	{
		for (int i = 0; i < sptr->totalconnections; i++) //for each connection...
		{
			if (sptr->connections[i].p_o.HasPendingPacket()) //If there are pending packets for this connection's packet manager
			{
				Packet p = sptr->connections[i].p_o.Retrieve_Pack(); //Retrieve packet from packet manager
				if (!sptr->sendall(i, p.buffer, p.size)) //send packet to connection
				{
					std::cout << "Failed to send packet to ID: " << i << std::endl; //Print out if failed to send packet
				}
				delete p.buffer; //Clean up buffer from the packet p
			}
		}
		Sleep(5);
	}
}
