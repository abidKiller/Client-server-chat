#pragma once
#include <fstream> //For ifstream/ofstream
struct FileTransferData
{
	static const int buffersize = 8192;
	std::string fileName; //For when receiving files
	int bytesWritten; //For when receiving files
	std::streampos fileOffset; //For when reading a file
	std::streampos fileSize; //For when reading a file
	std::streampos remainingBytes; //For when reading a file
	std::ifstream infileStream; //For reading a file that is being sent
	std::ofstream outfileStream; //For writing a file that is being received
};