#pragma once
#include <fstream>

struct FileTransferData
{
	static const int buffersize = 8192;
	std::string fileName; //when receiving files
	int byteswritten; //same
	int fileOffset; //when reading
	int fileSize; //same
	int remainingBytes;
	std::ifstream infileStream; //reading a file that's being sent
	std::ofstream outfileStream; //writing a file that's being received
	char buffer[buffersize];
};
