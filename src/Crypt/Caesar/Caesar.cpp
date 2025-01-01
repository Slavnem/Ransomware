// Slavnem @2024-12-14
// Caesar Src
#include <iostream>
#include <memory>

#include <Crypt/Caesar/Caesar.hpp>

// Crypt::Caesar
namespace Crypt
{
	namespace Caesar
	{
		// max & min
		static inline constexpr uint8_t CAESAR_KEY_MIN = 1;
		static inline constexpr uint8_t CAESAR_KEY_MAX = 255;
		static inline constexpr uint8_t CAESAR_KEY_DIFF = (CAESAR_KEY_MAX - CAESAR_KEY_MIN);
		static inline constexpr uint8_t CAESAR_KEY_NULL = (0 < CAESAR_KEY_MIN ? 0 : CAESAR_KEY_MIN - 1);

		// flags
		static inline constexpr uint8_t CAESAR_FLAG_NULL = (0 << 0);
		static inline constexpr uint8_t CAESAR_FLAG_ENCRYPT = (1 << 0);
		static inline constexpr uint8_t CAESAR_FLAG_DECRYPT = (1 << 1);
		static inline constexpr uint8_t CAESAR_FLAG_ERR = (1 << 2);

		// validKey
		bool validKey(const intmax_t _key)
		{
			return (_key >= CAESAR_KEY_MIN && _key <= CAESAR_KEY_MAX);
		}

		// default singleton instance
		std::shared_ptr<Caesar> Caesar::instance = nullptr;

		// constructor
		Caesar::Caesar(const uint8_t _key)
			: key(CAESAR_KEY_NULL),
			flag(CAESAR_FLAG_ERR)
		{
			// check if the key is valid
			if (!validKey(_key))
			{
				std::cerr << "[Crypt::Caesar] Crypt Key Has To Be Between "
					<< static_cast<int>(CAESAR_KEY_MIN) << " And " << static_cast<int>(CAESAR_KEY_MAX)
					<< std::endl;

				return;
			}

			// set the valid key and reset the flag
			resetFlag();
			setKey(_key);
		}

		// hasKey
		bool Caesar::hasKey() const
		{
			return validKey(static_cast<intmax_t>(key));
		}

		// isEncrypt
		bool Caesar::isEncrypt() const
		{
			return (flag & CAESAR_FLAG_ENCRYPT) != 0;
		}

		// isDecrypt
		bool Caesar::isDecrypt() const
		{
			return (flag & CAESAR_FLAG_DECRYPT) != 0;
		}

		// isErr
		bool Caesar::isErr() const
		{
			return (flag & CAESAR_FLAG_ERR);
		}

		// setKey
		void Caesar::setKey(const uint8_t _key)
		{
			key = validKey(_key) ? _key : CAESAR_KEY_NULL;
		}

		// getKey
		uint8_t Caesar::getKey() const
		{
			return key;
		}

		// encrypt
		void Caesar::encrypt(std::string& _text)
		{
			if (_text.empty())
			{
				resetFlag();
				setFlag(CAESAR_FLAG_ERR);

				std::cerr << "[Crypt::Caesar::Encrypt] Input Text Cannot Be Empty" << std::endl;
				return;
			}

			const size_t lengthText = _text.length();
			for (size_t i = 0; i < lengthText; i++)
			{
				_text[i] = static_cast<uint8_t>(((_text[i] + getKey()) % CAESAR_KEY_DIFF) + CAESAR_KEY_MIN);
			}

			removeFlag(CAESAR_FLAG_DECRYPT);
			setFlag(CAESAR_FLAG_ENCRYPT);
		}

		// decrypt
		void Caesar::decrypt(std::string& _text)
		{
			if (_text.empty())
			{
				resetFlag();
				setFlag(CAESAR_FLAG_NULL);

				std::cerr << "[Crypt::Caesar::Decrypt] Input Text Cannot Be Empty" << std::endl;
				return;
			}

			const size_t lengthText = _text.length();
			for (size_t i = 0; i < lengthText; i++)
			{
				_text[i] = static_cast<uint8_t>((((_text[i] - CAESAR_KEY_MIN) + CAESAR_KEY_DIFF) - getKey()) % CAESAR_KEY_DIFF);
			}

			removeFlag(CAESAR_FLAG_ENCRYPT);
			setFlag(CAESAR_FLAG_DECRYPT);
		}

		// get instance
		Caesar& Caesar::getInstance(const uint8_t _key)
		{
			// obj already has, return it
			if (instance)
				return *instance;

			// create new obj
			instance = std::make_unique<Caesar>(_key);
			return *instance;
		}

		// delete instance
		void Caesar::deleteInstance()
		{
			instance.reset(); // delete unique_ptr, will delete object auto
		}

		// print
		void Caesar::print() const
		{
			std::cout << "========== " << "CAESAR" << " =========="
				<< "\nKey: " << (hasKey() ? getKey() : CAESAR_KEY_NULL)
				<< "\nEncrypt: " << (isEncrypt() ? "Yes" : "No")
				<< "\nDecrypt: " << (isDecrypt() ? "Yes" : "No")
				<< std::endl;
		}
	}
}