/*
	Author: Slavnem
	Date: 25/12/2024
	Goal: Xor Encrypt & Decrypt
*/
#ifdef TEST_251220241336_XOR

#include <iostream>
#include <string>
#include <cstring>

#include <Crypt/Xor/Xor.hpp>
#include <Test/Test.hpp>

// main
int main()
{
	// run the tests
	std::string inputKey, inputText;

	std::cout << "Input the key: ";
	std::getline(std::cin, inputKey);

	std::cout << "Input the text: ";
	std::getline(std::cin, inputText);
	std::cout << std::endl;

	Crypt::Xor::Xor xorObj(inputKey);
	Test::ASSERT_EQ("Xor Object Has Key", xorObj.hasKey(), true);

	std::string encryptedText(inputText);
	xorObj.encrypt(encryptedText);
	Test::EXPECT_EQ("Xor Encrypt the Text", (strcmp(inputText.c_str(), encryptedText.c_str()) != 0), true);

	std::string decryptedText(encryptedText);
	xorObj.decrypt(decryptedText);
	Test::EXPECT_EQ("Xor Decrypt the Text", (strcmp(inputText.c_str(), decryptedText.c_str()) == 0), true);

	std::cout << "\n===== OUTPUT ====="
		<< "\nKey: " << inputKey
		<< "\nText: " << inputText
		<< "\nEncrypted: " << encryptedText
		<< "\nDecrypted: " << decryptedText
		<< std::endl;

	return 0;
}

#endif