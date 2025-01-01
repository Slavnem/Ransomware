// Slavnem @2024-12-24
// Xor
#ifndef CRPYT_XOR_INC_H
#define CRYPT_XOR_INC_H

#include <iostream>
#include <memory>

#include <Crypt/Crypt.hpp>

// Singleton Design Pattern
// Crypt::Xor
namespace Crypt
{
    namespace Xor
    {
        // validation
		bool validKey(const std::string& _key);

		// Xor
		class Xor : public Crypt<std::string, std::string>
		{
			private:
				std::string key; // encryption, decryption key
				uint8_t flag;

				Xor() = default; // block for create new public object
				static std::shared_ptr<Xor> instance;

			public:
				// block the assign operator
				Xor(const Xor&) = delete;
				Xor& operator=(const Xor&) = delete;

				// constructor
				explicit Xor(const std::string& key);

				// has validation
				bool hasKey() const override;

				// is validation
				bool isEncrypt() const override;
				bool isDecrypt() const override;
				bool isErr() const override;

				// setKey
				void setKey(const std::string& _key);

				// encrypt, decrypt
				void encrypt(std::string& _text) override;
				void decrypt(std::string& _text) override;

				// singleton
				static Xor& getInstance(const std::string& _shift = "");
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
				const std::string& getKey() const;
		};
    }
}

#endif // CRYPT_XOR_INC_H