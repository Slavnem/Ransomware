// Slavnem @2024-12-14 Debian 12
// Caesar Src

#include <iostream>
#include <Crypt/Caesar/Caesar.hpp>

// Crypt::Caesar
namespace Crypt
{
	// isKeyValid
	const bool Caesar::isKeyValid(const intmax_t _key)
	{
		return (_key >= Caesar::KEY_MIN && _key <= Caesar::KEY_MAX);
	}

	// doEncrypt
	uint8_t Caesar::doEncrypt(const uint8_t _char) const
	{
		/* Example:
			Encrypt Key: 36
			Encrpyted Value: 26
			Original Value: 220

			Min Limit: 10
			Max Limit: 255

			Formula: ((Original Value + Encrypt Key) % (Max Limit - Min Limit)) + Min Limit
			Result: ((220 + 36) % (255 - 10)) + 10
					(256 % 240) + 10 = 26
					(16 + 10) = 26
		*/
		return ((_char + key) % KEY_DIFF) + KEY_MIN;
	}

	// doDecypt
	uint8_t Caesar::doDecrypt(const uint8_t _char) const
	{
		/* Example:
			Encrypt Key: 20
			Encrypted Value: 5
			Original Value: 240

			Min Limit: 0
			Max Limit: 255

			Formula: (((Encrypted Value - Min Limit) + (Max Limit - Min Limit)) - Encrypt Key) % (Max Limit - Min Limit)
			Result: (((5 - 0) + (255 - 0)) - 20) % (255)
					((5 + 255) - 20) % 255
					(260 - 20) % 255
					(240 % 255) = 240
		*/
		return (((_char  - KEY_MIN) + KEY_DIFF) - this->key) % KEY_DIFF;
	}

	// default singleton instance
	Caesar* Caesar::instance = nullptr;

	// constructor
	Caesar::Caesar(const int16_t _key)
	{
		if (_key < KEY_MIN || _key > KEY_MAX)
			throw std::invalid_argument("Key Out Of Range!");

		key = static_cast<uint8_t>(_key);
	}

	// getInstance
	Caesar& Caesar::getInstance(const int16_t _key)
	{
		// obj already has, return it
		if (instance)
			return *instance;

		// create new obj
		instance = new Caesar(_key);
		return *instance;
	}

	// getEncrypt
	std::string Caesar::getEncrypt(std::string& _text)
	{
		// get text length and encrypt
		std::string tempText = _text;
		const size_t lengthText = tempText.length();

		for (size_t i = 0; i < lengthText; i++)
		{
			tempText[i] = static_cast<unsigned char>(doEncrypt(tempText[i]));
		}

		return tempText;
	}

	// getDecrypt
	std::string Caesar::getDecrypt(std::string& _text)
	{
		// get text length and decrypt
		std::string tempText = _text;
		const size_t lengthText = tempText.length();

		for (size_t i = 0; i < lengthText; i++)
		{
			tempText[i] = static_cast<unsigned char>(doDecrypt(tempText[i]));
		}

		return tempText;
	}
}