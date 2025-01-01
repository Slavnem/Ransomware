// Slavnem @2024-12-15
// CFile
#ifndef FILESTREAM_CFILE_INC_H
#define FILESTREAM_CFILE_INC_H

#include <iostream>
#include <cstdio>
#include <string>

#include "../FileStream.hpp"

// FileStream::CFile
namespace FileStream
{
	namespace CFile
	{
		class CFile : public FileStream<FILE, std::string, const char*>
		{
			private:
				fileopentype_t opentype;
				std::string path;
				FILE* file;
				uint8_t flag;

				CFile() = default; // block for create new public object

				// setFlag
				inline void setFlag(const uint8_t _flag)
				{
					flag |= _flag;
				}

				// resetFlag
				inline void resetFlag()
				{
					flag = 0;
				}

				// clearFlag
				inline void clearFlag(const uint8_t _flag)
				{
					flag &= ~_flag;
				}

				// hashFlag
				inline constexpr bool hashFlag(const uint8_t _flag) const
				{
					return (flag & _flag);
				}

				// set
				void setPath(std::string& _filepath) override;
				void setFile(const fileopentype_t _opentype) override;

			public:
				// constructor
				explicit CFile(std::string& _filepath, const fileopentype_t _opentype);

				// has validation
				bool hasPath() const override;
				bool hasFile() const override;

				// is validation
				bool isErr() const override;

				// get
				const char* getPath() const override;
				FILE* getFile() override;

				// abstract
				void write(const std::string& _text) override;
				const char* read() override;
				void close() override;
				void print() const override;
		};
	}
}

#endif // FILESTREAM_CFILE_INC_H