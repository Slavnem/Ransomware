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
#ifndef CRYPT_SCAESAR_INC_H
#define CRYPT_SCAESAR_INC_H

#include <iostream>
#include <Crypt/Caesar/Caesar.hpp>

// Singleton Design Pattern
// Crypt::Caesar::SCaesar
namespace Crypt
{
	namespace Caesar
	{
		namespace SCaesar
		{
			// name
			inline constexpr const char* const CRYPT_SCAESAR = "scaesar";

			// is validation
			bool isKeyValid(const std::string& _key);

			// Caesar
			class SCaesar : public Caesar
			{
				private:
					SCaesar() = default; // block for create new public object

				public:
					// block the assign operator
					SCaesar(const SCaesar&) = delete;
					SCaesar& operator=(const SCaesar&) = delete;

					// constructor
					explicit SCaesar(const std::string& key);

					// destructor
					~SCaesar() = default;

					// encrypt, decrypt
					virtual void encrypt(std::string* _text) override;
					virtual void decrypt(std::string* _text) override;

					// singleton
					static const SCaesar& getInstance(const std::string& _key = "");
					static void deleteInstance();

					// print
					virtual void print() const override;
			};
		}
	}
}

#endif // CRYPT_SCAESAR_INC_H