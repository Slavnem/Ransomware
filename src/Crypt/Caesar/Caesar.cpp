/***********************************************
 * Project Name     : Basic Caesar Encryption & Decryption
 * Author           : Slavnem
 * Date             : 14/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Basic Caesar encryption method that
					  encrypts and decrypts by key number to encrypt
					  ASCII text without exceeding the ASCII
					  character limit ASCII character limit
 ***********************************************/
#include <iostream>
#include <memory>

#include <Crypt/Caesar/Caesar.hpp>
#include <Exception/Exception.hpp>

// Crypt::Caesar
namespace Crypt
{
	namespace Caesar
	{
		// default singleton instance
		std::unique_ptr<Caesar> Caesar::instance = nullptr;

		// isKeyValid
		bool isKeyValid(const std::string& _key)
		{
			return (!_key.empty() && _key.length() > 0);
		}

		// constructor
		Caesar::Caesar(const std::string& _key)
			: key(CAESAR_KEY_NULL),
			flag(CAESAR_FLAG_ERR)
		{
			// check if the key is valid
			if (!isKeyValid(_key))
				throw Exception::Basic("[Caesar] Crypt Key Cannot Be Empty");

			// set the valid key and reset the flag
			this->resetFlag();
			this->setKey(_key);
		}

		// hasKey
		bool Caesar::hasKey() const
		{
			return isKeyValid(key);
		}

		// isEncrypt
		bool Caesar::isEncrypt() const
		{
			return (flag & CAESAR_FLAG_ENCRYPT) != 0;
		}

		// isDecrypt
		bool Caesar::isDecrypt() const
		{
			return (flag & CAESAR_FLAG_DECRYPT) != 0;
		}

		// isErr
		bool Caesar::isErr() const
		{
			return (flag & CAESAR_FLAG_ERR);
		}

		// setKey
		void Caesar::setKey(const std::string& _key)
		{
			key = isKeyValid(_key) ? _key : CAESAR_KEY_NULL;
		}

		// getKey
		const std::string& Caesar::getKey() const
		{
			return key;
		}

		// getFlag
		uint8_t Caesar::getFlag() const
		{
			return flag;
		}

		// setFlag
		void Caesar::setFlag(const uint8_t _flag)
		{
			flag |= _flag;
		}

		// resetFlag
		void Caesar::resetFlag()
		{
			flag = CAESAR_FLAG_NULL;
		}

		// removeFlag
		void Caesar::removeFlag(const uint8_t _flag)
		{
			flag &= ~_flag;
		}

		// encrypt
		/*
			Formula: Letter + Key
			Description: Basic Caesar encryption
		*/
		void Caesar::encrypt(std::string* _text)
		{
			// for the operation has to be ptr variable and text
			if (!_text || _text->empty())
				return;

			// using a temporary variable for easy access to the key's data
			const std::string& key = getKey();
    		if (key.empty())
    		    return;

			// instead of accessing variables with a continuous
			// function and losing time, we temporarily store
			// them in fixed variables
			const size_t lengthText = _text->length();
    		const size_t lengthKey = key.length();
    		const char* const cryptKey = key.data();

			// loop for processing from the beginning to the end of the text
			for (size_t i = 0; i < lengthText; i++)
			{
				// we move on to the next round when we encounter
				// some minor characters that might cause problems
				if ((*_text)[i] == '\n' || (*_text)[i] == ' ')
					continue;

				// encryption with formula
				(*_text)[i] += cryptKey[i % lengthKey];
			}

			// setting end-of-process flags
			this->removeFlag(CAESAR_FLAG_DECRYPT);
			this->setFlag(CAESAR_FLAG_ENCRYPT);
		}

		// decrypt
		/*
			Formula: Encrypted Key - Key
			Description: Basic Caesar decryption
		*/
		void Caesar::decrypt(std::string* _text)
		{
			// for the operation has to be ptr variable and text
			if (!_text || _text->empty())
				return;

			// using a temporary variable for easy access to the key's data
			const std::string& key = getKey();
    		if (key.empty())
    		    return;

			// instead of accessing variables with a continuous
			// function and losing time, we temporarily store
			// them in fixed variables
			const size_t lengthText = _text->length();
    		const size_t lengthKey = key.length();
    		const char* const cryptKey = key.data();

			// loop for processing from the beginning to the end of the text
			for (size_t i = 0; i < lengthText; i++)
			{
				// we move on to the next round when we encounter
				// some minor characters that might cause problems
				if ((*_text)[i] == '\n' || (*_text)[i] == ' ')
					continue;

				// decryption with formula
				(*_text)[i] -= cryptKey[i % lengthKey];
			}

			// setting end-of-process flags
			this->removeFlag(CAESAR_FLAG_ENCRYPT);
			this->setFlag(CAESAR_FLAG_DECRYPT);
		}

		// getInstance
		const Caesar& Caesar::getInstance(const std::string& _key)
		{
			// obj already has, return it
			if (instance)
				return *instance;

			// create new obj
			instance = std::make_unique<Caesar>(_key);
			return *instance;
		}

		// deleteInstance
		void Caesar::deleteInstance()
		{
			// delete unique_ptr, will delete object auto
			instance.reset();
		}

		// print
		void Caesar::print() const
		{
			// We output encryption type, key, encryption status, decryption status
			std::cout << "\n========== CAESAR =========="
				<< "\nKey: " << (this->getKey().data())
				<< "\nEncrypt: " << (this->isEncrypt() ? "Yes" : "No")
				<< "\nDecrypt: " << (this->isDecrypt() ? "Yes" : "No")
				<< std::endl;
		}
	}
}