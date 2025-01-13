/***********************************************
 * Project Name     : Crypt Encryption & Decryption Virtual Class
 * Author           : Slavnem
 * Date             : 14/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Crypt virtual class for inheritance
 ***********************************************/
#ifndef CRYPT_INC_H
#define CRYPT_INC_H

// Crypt
namespace Crypt
{
	// text
	inline constexpr const char* const CRYPT_TEXT_ENCRYPT = "encrypt";
	inline constexpr const char* const CRYPT_TEXT_DECRYPT = "decrypt";

	template<typename keyT, typename inputT>
	class Crypt
	{
		private:
			keyT key; // crypt key

		public:
			// has validation
			virtual bool hasKey() const = 0;

			// is validation
			virtual bool isEncrypt() const = 0;
			virtual bool isDecrypt() const = 0;
			virtual bool isErr() const = 0;

			// encrypt & decrypt
			virtual void encrypt(inputT* _data) = 0;
			virtual void decrypt(inputT* _data) = 0;

			// print
			virtual void print() const = 0;
	};
}

#endif // CRYPT_INC_H