// Slavnem @2024-12-14
// Caesar
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
		// validation
		bool validKey(const intmax_t _key);

		// Caesar
		class Caesar : public Crypt<uint8_t, std::string>
		{
			private:
				uint8_t key; // encryption, decryption key
				uint8_t flag;

				Caesar() = default; // block for create new public object
				static std::shared_ptr<Caesar> instance;

			public:
				// block the assign operator
				Caesar(const Caesar&) = delete;
				Caesar& operator=(const Caesar&) = delete;

				// constructor
				explicit Caesar(const uint8_t key);

				// has validation
				bool hasKey() const override;

				// is validation
				bool isEncrypt() const override;
				bool isDecrypt() const override;
				bool isErr() const override;

				// setKey
				void setKey(const uint8_t _key);

				// encrypt, decrypt
				void encrypt(std::string& _text) override;
				void decrypt(std::string& _text) override;

				// singleton
				static Caesar& getInstance(const uint8_t _shift = 0);
				static void deleteInstance();

				// print
				void print() const override;

				// set flag
				inline void setFlag(const uint8_t _flag)
				{
					flag |= _flag;
				}

				// remove flag
				inline void removeFlag(const uint8_t _flag)
				{
					flag &= ~_flag;
				}

				// reset flag
				inline void resetFlag()
				{
					flag = 0;
				}

			protected:
				// get key
				uint8_t getKey() const;
		};
	}
}

#endif // CRYPT_CAESAR_INC_H