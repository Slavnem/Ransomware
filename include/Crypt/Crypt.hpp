// Slavnem @2024-12-14 Debian 12
// Crypt
#ifndef CRYPT_INC_H
#define CRYPT_INC_H

#include <iostream>

// Crypt
namespace Crypt
{
	// argument text
	inline constexpr const char* const strEncrypt = "encrypt";
	inline constexpr const char* const strDecrypt = "decrypt";

	// flag
	inline constexpr size_t flagNull = (0 << 0);
	inline constexpr size_t flagEncrypt = (1 << 1);
	inline constexpr size_t flagDecrypt = (1 << 2);

	// Abstract Crypt Class
	class Crypt
	{
		public:
			// encrypt, decrypt
			virtual std::string getEncrypt(std::string& _text) = 0;
			virtual std::string getDecrypt(std::string& _text) = 0;
	};
}

#endif // CRYPT_INC_H