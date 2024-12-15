// Slavnem @2024-12-14 Debian 12
// Caesar
#ifndef CRYPT_CAESAR_INC_H
#define CRYPT_CAESAR_INC_H

#include <iostream>
#include <stdexcept>
#include <Crypt/Crypt.hpp>

// Singleton Design Pattern
// Crypt::Caesar
namespace Crypt
{
	// Caesar : Crypt
	class Caesar : public Crypt
	{
		private:
			uint8_t key; // encryption, decryption key
			Caesar() = default; // block for create new public object
			static Caesar* instance; // for singleton

			uint8_t doEncrypt(const uint8_t _char) const;
			uint8_t doDecrypt(const uint8_t _char) const;

		public:
			// constructor
			explicit Caesar(const int16_t _key);

			// encrypt, decrypt
			std::string getEncrypt(std::string& _text) override;
			std::string getDecrypt(std::string& _text) override;

			// validation
			static const bool isKeyValid(const intmax_t _key);

			// singleton
			static Caesar& getInstance(const int16_t _shift = 0);

		protected:
			// max & min
			static constexpr uint8_t KEY_MAX = 255;
			static constexpr uint8_t KEY_MIN = 1;
			static constexpr uint8_t KEY_DIFF = (KEY_MAX - KEY_MIN);
	};
}

#endif // CRYPT_CAESAR_INC_H