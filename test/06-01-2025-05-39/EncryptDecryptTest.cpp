/***********************************************
 * Project Name     : Encrypt & Decrypt
 * Author           : Slavnem
 * Date             : 06/01/2025
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Encrypt & Decrypt Test
 * Status			: Tested
 ***********************************************/
#ifdef TEST_060120250539_ENCRYPTDECRYPT

#include <iostream>
#include <cstring>

#include <Test/Test.hpp>
#include <FileStream/CFile/CFile.hpp>
#include <Crypt/Caesar/Caesar.hpp>
#include <Crypt/Caesar/SCaesar/SCaesar.hpp>

// main
int main()
{
	std::string cryptKey;
	std::string filepath("test.txt");
	std::string crypttype;

	Test::ASSERT_EQ("Filename Is True", strcmp(filepath.data(), "test.txt") == 0, true);

	bool choiceEncrypt = false;

	// get
	std::cout << "Encrypt Key: ";
	std::getline(std::cin, cryptKey);
	Test::ASSERT_EQ("Crypt Key Is Valid", Crypt::Caesar::isKeyValid(cryptKey), true);

	std::cout << "Encrypt or Decrypt: ";
	std::getline(std::cin, crypttype);

	choiceEncrypt = (strcmp(crypttype.data(), Crypt::CRYPT_TEXT_ENCRYPT) == 0);

	// crypt obj
	Crypt::Caesar::SCaesar::SCaesar cryptObject(cryptKey);

	// filestream obj
	FileStream::CFile::CFile filestreamObject(filepath, FileStream::EFILEOPEN_READWRITE);

	// check err status
	Test::ASSERT_EQ("Crypt & FileStream Object Has", cryptObject.isErr() || filestreamObject.isErr(), false);

	// encrypt or decrypt
	std::string* data = filestreamObject.readLine(true);

	// data not found
	if (!Test::EXPECT_EQ("Run Encrypt or Decrypt", data != nullptr, true))
		goto print;

	// encrypt & decrypt
	switch (choiceEncrypt)
	{
		case true: // encrypt
			while (data && !data->empty())
			{
				cryptObject.encrypt(data);

				if(!filestreamObject.writeLine(data))
					break;

				filestreamObject.nextLine();
				data = filestreamObject.readLine(true);
			}
			break;
		default: // decrypt
			while (data && !data->empty())
			{
				cryptObject.decrypt(data);

				if(!filestreamObject.writeLine(data))
					break;

				filestreamObject.nextLine();
				data = filestreamObject.readLine(true);
			}
	}

	// close the file
	filestreamObject.closeFile();

	// is file closed
	Test::EXPECT_EQ("File Is Closed Successfully", filestreamObject.hasFile(), false);

	// end
	print:
		cryptObject.print();
		filestreamObject.print();
}

#endif // TEST_060120250539_ENCRYPTDECRYPT