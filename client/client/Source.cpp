#include "pch.h"
//client
#include "Client.h"

int main()
{
	Client myClient("127.0.0.1", 1111);

	if (!myClient.ConnectServer()) //If client fails to connect...
	{
		cout << "Failed to connect to server..." << endl;
		system("pause");
		return 1;
	}

	myClient.RequestFile("b6-2.jpg");
	std::string userinput; //holds the user's chat message
	while (true)
	{
		getline(cin, userinput); //Get line if user presses enter and fill the buffer
		if (!myClient.SendString(userinput)) {		//send string to server
			break;		//if send string failed	leave loop as server connection lost	//
		}
		Sleep(10);
	}


	system("pause");
	return 0;
}