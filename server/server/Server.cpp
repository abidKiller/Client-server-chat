#include "Server.h"

Server::Server(int PORT, bool BroadcastPublically)
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
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally

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
}

bool Server::ListenForNewConnection()
{
	SOCKET newConn;
	int conn_count = 0;
	newConn = accept(slisten, (SOCKADDR*)&addr, &addrlen);
	if (newConn == 0)
	{
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}
	else {
		std::cout << "client connected!!" << std::endl;
		connections[totalconnections] = newConn;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(totalconnections), NULL, NULL); //To Create Thread to handle this client.
		std::string MOTD = "MOTD: Welcome! This is the message of the day!.";
		SendString(totalconnections, MOTD);
		totalconnections++;
	}
}

bool Server::ProcessPacket(int index, Packet pack_type)
{
	switch (pack_type)
	{
	case P_ChatMessage://braces used so that variables can be declared
	{
		std::string Message; //string to store our message we received
		if (!GetString(index, Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false

		for (int i = 0; i < totalconnections; i++) //Next we need to send the message out to each user
		{
			if (i == index) //If connection is the user who sent the message...
				continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
			if (!SendString(i, Message)) //Send message to connection at index i, if message fails to be sent...
			{
				std::cout << "Failed to send message from client index: " << index << " to client index: " << i << std::endl;
			}
		}
		std::cout << "Processed chat message packet from user index: " << index << std::endl;

		break;
	}
	default:
		std::cout << "Unknown packet received." << std::endl;
		break;
	}
	return true;//did not handle the proceess for not processing packet
}

void Server::ClientHandlerThread(int index)
{
	Packet pack_type;
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
	closesocket(sptr->connections[index]);
}