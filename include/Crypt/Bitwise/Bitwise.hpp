/***********************************************
 * Project Name     : Bitwise Encryption & Decryption
 * Author           : Slavnem
 * Date             : 02/01/2025
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : This program aims to perform encryption
 *                    and decryption using the bitwise operations
 *                    of a computer operating in binary.
 ***********************************************/
#ifndef CRYPT_BITWISE_INC_H
#define CRYPT_BITWISE_INC_H

#include <iostream>
#include <memory>

#include <Crypt/Crypt.hpp>

// Crypt::Bitwise
namespace Crypt
{
	namespace Bitwise
	{
		// name
		inline constexpr const char* const CRYPT_BITWISE = "bitwise";

		// key
		inline constexpr const char* const BITWISE_KEY_NULL = "";

		// flags
		inline constexpr uint8_t BITWISE_FLAG_NULL = (0 << 0);
		inline constexpr uint8_t BITWISE_FLAG_ENCRYPT = (1 << 0);
		inline constexpr uint8_t BITWISE_FLAG_DECRYPT = (1 << 1);
		inline constexpr uint8_t BITWISE_FLAG_ERR = (1 << 2);

		// is validation
		bool isKeyValid(const std::string& _key);

		class Bitwise : public Crypt<std::string, std::string>
		{
			private:
				std::string key; // encryption, decryption key
				uint8_t flag;
				static std::unique_ptr<Bitwise> instance;

				Bitwise() = default; // block for create new public object

			public:
				// block
				Bitwise(const Bitwise&) = delete;
				Bitwise& operator=(const Bitwise&) = delete;

				// constructor
				explicit Bitwise(const std::string& _key);

				// destructor
				~Bitwise() = default;

				// has validation
				virtual bool hasKey() const override;

				// is validation
				virtual bool isEncrypt() const override;
				virtual bool isDecrypt() const override;
				virtual bool isErr() const override;

				// set key
				virtual void setKey(const std::string& _key);

				// encrypt, decrypt
				virtual void encrypt(std::string* _text);
				virtual void decrypt(std::string* _text);

				// singleton
				static const Bitwise& getInstance(const std::string& _key = "");
				static void deleteInstance();

				// print
				virtual void print() const override;

			protected:
				// get key
				virtual const std::string& getKey() const;

				// get, set, reset, remove flag
				virtual uint8_t getFlag() const;
				virtual void setFlag(const uint8_t _flag);
				virtual void resetFlag();
				virtual void removeFlag(const uint8_t _flag);
		};
	}
}

#endif // CRYPT_BITWISE_INC_H