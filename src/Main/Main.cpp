/***********************************************
 * Project Name     : Main
 * Author           : Slavnem
 * Date             : 15/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Main
 ***********************************************/
#ifdef MAIN

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>

#include <FileStream/FileStream.hpp>
#include <FileStream/CFile/CFile.hpp>

#include <Crypt/Crypt.hpp>
#include <Crypt/Caesar/Caesar.hpp>
#include <Crypt/Caesar/SCaesar/SCaesar.hpp>
#include <Crypt/Bitwise/Bitwise.hpp>

#include <Exception/Exception.hpp>

// main
int main(const int argc, const char* const argv[])
{
	// not enough arguments
	if (argc < 5)
		return 1;

	std::vector<std::string> arguments(argv, argv + argc);
	std::string cryptClass(argv[1]);
	std::string cryptKey(argv[2]);
	std::string filepath(argc > 5 ? arguments[5] : arguments[4]);

	bool choiceEncrypt = false;
	bool endPrint = false;

	// crypt object
	std::unique_ptr<Crypt::Crypt<std::string, std::string>> cryptObject;

	// caesar
	if (strcmp(cryptClass.data(), Crypt::Caesar::CRYPT_CAESAR) == 0)
		cryptObject = std::make_unique<Crypt::Caesar::Caesar>(cryptKey);
	// scaesar
	else if (strcmp(cryptClass.data(), Crypt::Caesar::SCaesar::CRYPT_SCAESAR) == 0)
		cryptObject = std::make_unique<Crypt::Caesar::SCaesar::SCaesar>(cryptKey);
	// bitwise
	else if (strcmp(cryptClass.data(), Crypt::Bitwise::CRYPT_BITWISE) == 0)
		cryptObject = std::make_unique<Crypt::Bitwise::Bitwise>(cryptKey);
	// unsupported
	else
		throw Exception::Critical("[MAIN] Unknown Crypt Class");

	// encrypt or decrypt
	choiceEncrypt = (strcmp(arguments[3].data(), Crypt::CRYPT_TEXT_ENCRYPT) == 0);

	// print or not print
	if (argc > 5)
		endPrint = (strcmp(arguments[4].data(), "print") == 0);

	// filestream obj
	std::unique_ptr<FileStream::CFile::CFile> filestreamObject;
	filestreamObject = std::make_unique<FileStream::CFile::CFile>(filepath, FileStream::EFILEOPEN_READWRITE);

	// check err status
	if(cryptObject->isErr() || filestreamObject->isErr())
		exit(EXIT_FAILURE);

	// encrypt or decrypt
	std::string* data = filestreamObject->readLine(true);

	// data not found
	if(!data || data->empty())
		goto end;

	// encrypt & decrypt
	switch (choiceEncrypt)
	{
		case true: // encrypt
			while (data && !data->empty())
			{
				cryptObject->encrypt(data);

				if (!filestreamObject->writeLine(data))
					break;

				filestreamObject->nextLine();
				data = filestreamObject->readLine(true);
			}
		break;
		default: // decrypt
			while (data && !data->empty())
			{
				cryptObject->decrypt(data);

				if (!filestreamObject->writeLine(data))
					break;

				filestreamObject->nextLine();
				data = filestreamObject->readLine(true);
			}
	}

	end:
		// terminate the self
		if(!endPrint)
			exit(EXIT_SUCCESS);

	// print
	cryptObject->print();
	filestreamObject->print();
}

#endif