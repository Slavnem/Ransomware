/***********************************************
 * Project Name     : Customized Caesar Encryption & Decryption
 * Author           : Slavnem
 * Date             : 14/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Customized Caesar encryption method that
					  encrypts and decrypts by key number to encrypt
					  ASCII text without exceeding the ASCII
					  character limit ASCII character limit
 ***********************************************/
#ifndef CRYPT_CAESAR_INC_H
#define CRYPT_CAESAR_INC_H

#include <iostream>
#include <memory>

#include <Crypt/Crypt.hpp>

// Singleton Design Pattern
// Crypt::Caesar
namespace Crypt
{
	namespace Caesar
	{
		// name
		inline constexpr const char* const CRYPT_CAESAR = "caesar";

		// key
		inline constexpr const char* const CAESAR_KEY_NULL = "";

		// flags
		inline constexpr uint8_t CAESAR_FLAG_NULL = (0 << 0);
		inline constexpr uint8_t CAESAR_FLAG_ENCRYPT = (1 << 0);
		inline constexpr uint8_t CAESAR_FLAG_DECRYPT = (1 << 1);
		inline constexpr uint8_t CAESAR_FLAG_ERR = (1 << 2);

		// is validation
		bool isKeyValid(const std::string& _key);

		// Caesar
		class Caesar : public Crypt<std::string, std::string>
		{
			private:
				std::string key; // encryption, decryption key
				uint8_t flag;

				Caesar() = default; // block for create new public object
				static std::unique_ptr<Caesar> instance;

			public:
				// block the assign operator
				Caesar(const Caesar&) = delete;
				Caesar& operator=(const Caesar&) = delete;

				// constructor
				explicit Caesar(const std::string& key);

				// destructor
				virtual ~Caesar() = default;

				// has validation
				virtual bool hasKey() const override;

				// is validation
				virtual bool isEncrypt() const override;
				virtual bool isDecrypt() const override;
				virtual bool isErr() const override;

				// setKey
				virtual void setKey(const std::string& _key);

				// encrypt, decrypt
				virtual void encrypt(std::string* _text) override;
				virtual void decrypt(std::string* _text) override;

				// singleton
				static const Caesar& getInstance(const std::string& _key = "");
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

#endif // CRYPT_CAESAR_INC_H