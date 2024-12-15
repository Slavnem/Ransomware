// Slavnem @2024-12-15 Debian 12
// Main

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include <Crypt/Crypt.hpp>
#include <Crypt/Caesar/Caesar.hpp>

#include <FileStream/FileStream.hpp>
#include <FileStream/CFile/CFile.hpp>

// main
int main(const int argc, const char* const argv[])
{
	uint8_t cryptKey = 0;
	uint8_t flagEncrypt = Crypt::flagNull;
	uint8_t noPrint = 0;
	std::string filepath = "";
	std::vector<std::string> arguments(argv, argv + argc);

	// arg: encrypt key
	if (argc > 1) // convert to num
		cryptKey = static_cast<uint8_t>(std::strtoul(arguments[1].c_str(), nullptr, 0));

	// encrypt key status
	if (!Crypt::Caesar::isKeyValid(cryptKey))
	{
		std::cerr << "[ERROR] Encryption Key Is Invalid!" << std::endl;
		return 0;
	}

	// encrypt or decrypt, read
	if (argc > 2)
	{
		flagEncrypt = (strcmp(arguments[2].c_str(), Crypt::strEncrypt) == 0) ?
			Crypt::flagEncrypt : Crypt::flagDecrypt;
	}

	// whether to print data to the console or not
	if (argc > 4)
	{
		noPrint = (strcmp(arguments[3].c_str(), "noprint") == 0);
		filepath = arguments[4];
	}

	// do not print, only do your job :(
	// get filepath
	if (argc == 4)
		filepath = arguments[3];

	// create file obj and check file
	FileStream::CFile fileObj(filepath, FileStream::EFILEOPEN_READWRITE);

	// file not exist
	if(!fileObj.isOpen())
		exit(EXIT_FAILURE);

	// crypt object
	Crypt::Caesar cryptObj(cryptKey);

	// set file position
	FILE* myfile = fileObj.getFile();
	fseek(myfile, 0, SEEK_SET);

	// buffer and current position
	const uint16_t bufferSize = 512;
	char buffer[bufferSize];

	// file position
	long currentFilePosition = ftell(myfile);

	// encrypt
	if (flagEncrypt & static_cast<uint8_t>(Crypt::flagEncrypt))
	{
		// encrypt
		while (fgets(buffer, bufferSize, myfile))
		{
			// convert text to string obj and encrypt the text
			std::string data(buffer);
			std::string encrypted = cryptObj.getEncrypt(data);

			// set the old file position
			fseek(myfile, currentFilePosition, SEEK_SET);

			// write data to file
			fileObj.write(encrypted);

			// get current file position
			currentFilePosition = ftell(myfile);
		}
	}
	else
	{
		// decrypt
		while (fgets(buffer, bufferSize, myfile))
		{
			// convert text to string obj and decrypt the text
			std::string data(buffer);
			std::string decrypted = cryptObj.getDecrypt(data);

			// set the old file position
			fseek(myfile, currentFilePosition, SEEK_SET);

			// write data to file
			fileObj.write(decrypted);

			// get current file position
			currentFilePosition = ftell(myfile);
		}
	}

	// do not print
	if (noPrint)
	{
		fileObj.~CFile();
		return 0;
	}

	// print the crypt type
	std::cout << "Type: " << ((flagEncrypt & Crypt::flagEncrypt) ? "Encrypt" : "Decrypt")
		<< std::endl;

	// print infos about file
	fileObj.print();

	// destroy! butterfly
	fileObj.~CFile();
}