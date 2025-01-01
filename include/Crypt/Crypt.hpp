// Slavnem @2024-12-14
// Crypt
#ifndef CRYPT_INC_H
#define CRYPT_INC_H


// Crypt
namespace Crypt
{
	// text
	static inline constexpr const char* const TEXT_ENCRYPT = "encrypt";
	static inline constexpr const char* const TEXT_DECRYPT = "decrypt";

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
			virtual void encrypt(inputT& _data) = 0;
			virtual void decrypt(inputT& _data) = 0;

			// print
			virtual void print() const = 0;
	};
}

#endif // CRYPT_INC_H