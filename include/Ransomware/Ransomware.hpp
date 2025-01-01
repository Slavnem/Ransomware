// Slavnem @2024-12-29
// Ransomware
#ifndef RANSOMWARE_INC_H
#define RANSOMWARE_INC_H

#include <iostream>

#include <Crypt/Crypt.hpp>
#include <FileStream/FileStream.hpp>

// Singleton Design Pattern
// Ransomware
namespace Ransomware
{
	// Ransomware::Ransomware
	template<typename CryptT, typename FileStreamT>
	class Ransomware
	{
		private:
			CryptT* crypt;
			FileStreamT* filestream;

			Ransomware() = default; // block for create new public object

		public:
			explicit Ransomware(CryptT* _cryptobj, FileStreamT* _filestreamobj)
				: crypt(_cryptobj), filestream(_filestreamobj)
			{
				if(!crypt || crypt->isErr())
				{
					std::cerr << "[Ransomware::Ransomware] Crypt Object Has To Be Member Of Crypt Class" << std::endl;
					throw;
				}

				if(!filestream || filestream->isErr())
				{
					std::cerr << "[Ransomware::Ransomware] FileStream Object Has To Be Member Of FileStream Class" << std::endl;
					throw;
				}
			}

			virtual ~Ransomware() = default;

			virtual CryptT& getCrypt() const
			{
				return *crypt;
			}

			virtual FileStreamT& getFileStream() const
			{
				return *filestream;
			}

			virtual bool hasCrypt() const
			{
				return (crypt && !crypt->isErr());
			}

			virtual bool hasFileStream() const
			{
				return (filestream && !filestream->isErr());
			}

			virtual bool isErr() const
			{
				return (!crypt || !filestream || crypt->isErr() || filestream->isErr());
			}

			virtual void runEncrypt()
			{
				std::cout << "Run Encrypt..." << std::endl;
			}

			virtual void runDecrypt()
			{
				std::cout << "Run Decrypt..." << std::endl;
			}

			virtual void print() const
			{
				std::cout << "========== RANSOMWARE ==========" << std::endl;

				crypt->print();
				filestream->print();
			}

			// block the assign operator
			Ransomware(const Ransomware&) = delete;
			Ransomware& operator=(const Ransomware&) = delete;
	};
}

#endif // RANSOMWARE_INC_H