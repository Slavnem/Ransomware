/***********************************************
 * Project Name     : Customized SCaesar Encryption & Decryption
 * Author           : Slavnem
 * Date             : 11/01/2025
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Customized SCaesar encryption method that
					  encrypts and decrypts by key number to encrypt
					  ASCII text without exceeding the ASCII
					  character limit ASCII character limit
 ***********************************************/
#include <iostream>

#include <Crypt/Caesar/Caesar.hpp>
#include <Crypt/Caesar/SCaesar/SCaesar.hpp>
#include <Exception/Exception.hpp>

// Crypt::Caesar::SCaesar
namespace Crypt
{
	namespace Caesar
	{
		namespace SCaesar
		{
			// max & min
			static inline constexpr uint8_t SCAESAR_KEY_MIN = 0;
			static inline constexpr uint8_t SCAESAR_KEY_MAX = 255;
			static inline constexpr uint8_t SCAESAR_KEY_DIFF = (SCAESAR_KEY_MAX - SCAESAR_KEY_MIN);

			// isKeyValid
			bool isKeyValid(const std::string& _key)
			{
				return ::Crypt::Caesar::isKeyValid(_key);
			}

			// constructor
			SCaesar::SCaesar(const std::string& _key)
				: Caesar(_key)
			{
				// check if the key is valid
				if (!isKeyValid(_key))
					throw Exception::Basic("[SCaesar] Crypt Key Cannot Be Empty");

				// set the valid key and reset the flag
				Caesar::resetFlag();
				Caesar::setKey(_key);
			}

			// encrypt
			/*
				Formula:
					unsigned int 16bit ((Letter + Key) - Max Key Limit) + (Max Key Limit - Min Key Limit)

				Description: Our ciphertext may exceed the extended ASCII character limit and this is
					fine because it is an unreadable ciphertext.

					First, as in real SCaesar encryption, we add the character and the cipher number.
					Then we subtract the largest number from the number we have now found to prevent some overflow.
					Then we add the difference between the largest and the smallest number to the final number,
					so that we don't get a negative number, and we get an encrypted number that doesn't exceed
					the maximum character limit, or exceed it 2 or more times. This makes it easier to decrypt
					the encrypted number and much harder to find the logic of the encryption method!
					The only problem is that the character has to be in the ASCII character set.
			*/
			void SCaesar::encrypt(std::string* _text)
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
					(*_text)[i] = static_cast<uint16_t>((((*_text)[i] + cryptKey[i % lengthKey]) - SCAESAR_KEY_MAX) + (SCAESAR_KEY_DIFF));
				}

				// setting end-of-process flags
				Caesar::removeFlag(CAESAR_FLAG_DECRYPT);
				Caesar::setFlag(CAESAR_FLAG_ENCRYPT);
			}

			// decrypt
			/*
				Formula: unsigned char (((Encrypted Number - (Max Key Limit - Min Key Limit)) + Max Key Limit) - Key)

				Description: We do the opposite of what we did in the encryption process and rewind the process so
					that we have access to the main letter and we do not find a negative value or
					an unlisted value thanks to the delimitation operations we have done.
					since it is limited to the extended ASCII character set, we convert the last number to
					ASCII characters and thus find the original letter.
			*/
			void SCaesar::decrypt(std::string* _text)
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
					(*_text)[i] = static_cast<unsigned char>((((*_text)[i] - SCAESAR_KEY_DIFF) + SCAESAR_KEY_MAX) - cryptKey[i % lengthKey]);
				}

				// setting end-of-process flags
				Caesar::removeFlag(CAESAR_FLAG_ENCRYPT);
				Caesar::setFlag(CAESAR_FLAG_DECRYPT);
			}

			// getInstance
			const SCaesar& SCaesar::getInstance(const std::string& _key)
			{
				// return the pointer we accessed using the parent type to our type
				return dynamic_cast<const SCaesar&>(Caesar::Caesar::getInstance(_key));
			}

			// deleteInstance
			void SCaesar::deleteInstance()
			{
				// delete unique_ptr, will delete object auto
				Caesar::deleteInstance();
			}

			// print
			void SCaesar::print() const
			{
				// We output encryption type, key, encryption status, decryption status
				std::cout << "\n========== SCAESAR =========="
					<< "\nKey: " << (Caesar::getKey().data())
					<< "\nEncrypt: " << (Caesar::isEncrypt() ? "Yes" : "No")
					<< "\nDecrypt: " << (Caesar::isDecrypt() ? "Yes" : "No")
					<< std::endl;
			}
		}
	}
}