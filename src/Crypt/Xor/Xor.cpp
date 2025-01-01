// Slavnem @2024-12-14
// Xor Src
#include <iostream>
#include <memory>

#include <Crypt/Xor/Xor.hpp>

// Crypt::Xor
namespace Crypt
{
	namespace Xor
	{
        // key
        static inline constexpr const char* const XOR_KEY_NULL = "";

		// flags
		static inline constexpr uint8_t XOR_FLAG_NULL = (0 << 0);
		static inline constexpr uint8_t XOR_FLAG_ENCRYPT = (1 << 0);
		static inline constexpr uint8_t XOR_FLAG_DECRYPT = (1 << 1);
		static inline constexpr uint8_t XOR_FLAG_ERR = (1 << 2);

		// validKey
		bool validKey(const std::string& _key)
		{
			return (!_key.empty() && _key.length() > 0);
		}

		// default singleton instance
		std::shared_ptr<Xor> Xor::instance = nullptr;

		// constructor
		Xor::Xor(const std::string& _key)
			: key(""),
			flag(XOR_FLAG_ERR)
		{
			// check if the key is valid
			if (!validKey(_key))
			{
				std::cerr << "[Crypt::Xor] Crypt Key Cannot Be Null" << std::endl;
				return;
			}

			// set the valid key and reset the flag
			resetFlag();
			setKey(_key);
		}

		// hasKey
		bool Xor::hasKey() const
		{
			return validKey(key);
		}

		// isEncrypt
		bool Xor::isEncrypt() const
		{
			return (flag & XOR_FLAG_ENCRYPT) != 0;
		}

		// isDecrypt
		bool Xor::isDecrypt() const
		{
			return (flag & XOR_FLAG_DECRYPT) != 0;
		}

		// isErr
		bool Xor::isErr() const
		{
			return (flag & XOR_FLAG_ERR);
		}

		// setKey
		void Xor::setKey(const std::string& _key)
		{
			key = validKey(_key) ? _key.data() : XOR_KEY_NULL;
		}

		// getKey
		const std::string& Xor::getKey() const
		{
			return key;
		}

		// encrypt
		void Xor::encrypt(std::string& _text)
		{
			if (_text.empty())
			{
				resetFlag();
				setFlag(XOR_FLAG_ERR);

				std::cerr << "[Crypt::Xor::Encrypt] Input Text Cannot Be Empty" << std::endl;
				return;
			}

			const size_t lengthText = _text.length();
			const size_t lengthKey = key.length();

			for (size_t i = 0; i < lengthText; i++)
			{
				_text[i] ^= (getKey().data()[i % lengthKey]);
			}

			removeFlag(XOR_FLAG_DECRYPT);
			setFlag(XOR_FLAG_ENCRYPT);
		}

		// decrypt
		void Xor::decrypt(std::string& _text)
		{
			if (_text.empty())
			{
				resetFlag();
				setFlag(XOR_FLAG_NULL);

				std::cerr << "[Crypt::Xor::Decrypt] Input Text Cannot Be Empty" << std::endl;
				return;
			}

			const size_t lengthText = _text.length();
			const size_t lengthKey = key.length();

			for (size_t i = 0; i < lengthText; i++)
			{
                _text[i] ^= (getKey().data()[i % lengthKey]);
			}

			removeFlag(XOR_FLAG_ENCRYPT);
			setFlag(XOR_FLAG_DECRYPT);
		}

		// get instance
		Xor& Xor::getInstance(const std::string& _key)
		{
			// obj already has, return it
			if (instance)
				return *instance;

			// create new obj
			instance = std::make_unique<Xor>(_key);
			return *instance;
		}

		// delete instance
		void Xor::deleteInstance()
		{
			instance.reset(); // delete unique_ptr, will delete object auto
		}

		// print
		void Xor::print() const
		{
			std::cout << "========== " << "Xor" << " =========="
				<< "\nKey: " << (hasKey() ? getKey().data() : "")
				<< "\nEncrypt: " << (isEncrypt() ? "Yes" : "No")
				<< "\nDecrypt: " << (isDecrypt() ? "Yes" : "No")
				<< std::endl;
		}
	}
}