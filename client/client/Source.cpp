//client
#include "Client.h"

int main()
{
	Client myClient("127.0.0.1", 1111);

	if (!myClient.ConnectServer()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}

	std::string userinput; //holds the user's chat message
	while (true)
	{
		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
		if (!myClient.SendString(userinput)) {		//send string to server
			break;		//if send string failed	leave loop as server connection lost	//
		}
		Sleep(10);
	}


	system("pause");
	return 0;
}