/***********************************************
 * Project Name     : Bitwise Encryption & Decryption
 * Author           : Slavnem
 * Date             : 02/01/2025
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : The key can consist of regular text and the
					  encryption key must not be empty, it must
					  contain at least 1 character. Encryption
					  and decryption are not active because the
					  encryption algorithm is not specified.
					  Some general functions are available,
					  but can be improved in the new version
 ***********************************************/
#include <iostream>
#include <memory>

#include <Crypt/Bitwise/Bitwise.hpp>
#include <Exception/Exception.hpp>

// Crypt::Bitwise
namespace Crypt
{
	namespace Bitwise
	{
		// default singleton instance
		std::unique_ptr<Bitwise> Bitwise::instance = nullptr;

		// isKeyValid
		bool isKeyValid(const std::string& _key)
		{
			return (!_key.empty() && _key.length() > 0);
		}

		// Bitwise
		Bitwise::Bitwise(const std::string& _key)
			: key(BITWISE_KEY_NULL), flag(BITWISE_FLAG_ERR)
		{
			// check if the key is valid
			if (!isKeyValid(_key))
				throw Exception::Basic("[Bitwise] Key is not valid");

			// set the valid key and reset the flag
			this->setKey(_key);
			this->resetFlag();
		}

		// hasKey
		bool Bitwise::hasKey() const
		{
			return (!key.empty() && key.length() > 0);
		}

		// isEncrypt
		bool Bitwise::isEncrypt() const
		{
			return (flag & BITWISE_FLAG_ENCRYPT);
		}

		// isDecrypt
		bool Bitwise::isDecrypt() const
		{
			return (flag & BITWISE_FLAG_DECRYPT);
		}

		// isErr
		bool Bitwise::isErr() const
		{
			return (!hasKey() || (flag & BITWISE_FLAG_ERR));
		}

		// getKey
		const std::string& Bitwise::getKey() const
		{
			return key;
		}

		// getFlag
		uint8_t Bitwise::getFlag() const
		{
			return flag;
		}

		// setFlag
		void Bitwise::setFlag(const uint8_t _flag)
		{
			flag |= _flag;
		}

		// resetFlag
		void Bitwise::resetFlag()
		{
			flag = BITWISE_FLAG_NULL;
		}

		// removeFlag
		void Bitwise::removeFlag(const uint8_t _flag)
		{
			flag &= ~_flag;
		}

		// setKey
		void Bitwise::setKey(const std::string& _key)
		{
			key = isKeyValid(_key) ? _key : BITWISE_KEY_NULL;
		}

		// encrypt
		void Bitwise::encrypt(std::string* _text)
		{
			(void)_text; // gcc unused variable warn ignore
			return;
		}

		// decrypt
		void Bitwise::decrypt(std::string* _text)
		{
			(void)_text; // gcc unused variable warn ignore
			return;
		}

		// getInstance
		const Bitwise& Bitwise::getInstance(const std::string& _key)
		{
			// obj already has, return it
			if (instance)
				return *instance;

			// create new obj
			instance = std::make_unique<Bitwise>(_key);
			return *instance;
		}

		// deleteInstance
		void Bitwise::deleteInstance()
		{
			// delete unique_ptr, will delete object auto
			instance.reset();
		}

		// print
		void Bitwise::print() const
		{
			// We output encryption type, key, encryption status, decryption status
			std::cout << "\n========== BITWISE =========="
				<< "\nKey: " << (this->getKey().data())
				<< "\nEncrypted: " << (this->isEncrypt() ? "Yes" : "No")
				<< "\nDecrypted: " << (this->isDecrypt() ? "Yes" : "No")
				<< std::endl;
		}
	}
}