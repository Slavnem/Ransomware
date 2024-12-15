// Slavnem @2024-12-15 Debian 12
// CFile
#ifndef FILESTREAM_CFILE_INC_H
#define FILESTREAM_CFILE_INC_H

#include <iostream>
#include <cstdio>
#include <FileStream/FileStream.hpp>

// FileStream::CFile
namespace FileStream
{
    class CFile : public FileStream
	{
		private:
            uint8_t flag;
			FILE* file;
            std::string path;

            // setFileFlag
			void setFileFlag(const uint8_t _flag)
			{
                flag |= _flag;
            }

            // resetFileFlag
            inline constexpr void resetFileFlag()
            {
                flag = 0;
            }

            // clearFileFlag
			inline constexpr void clearFileFlag(const uint8_t _flag)
            {
                flag &= ~_flag;
            }

            // hashFileFlag
			constexpr bool hashFileFlag(const uint8_t _flag) const
            {
                return flag & _flag;
            }

			bool setOpen(const std::string& _filepath, const enum FileOpenType _opentype);
			void setPath(const std::string& _filepath);

		public:
			CFile(const std::string& _filepath, const enum FileOpenType _opentype);

			bool isOpen() const;

			FILE* getFile();
			std::string getPath() const;
			
			virtual void write(const std::string& _text) override;
			virtual void close() override;
			virtual void print() const override;
			virtual ~CFile();
	};
}

#endif // FILESTREAM_CFILE_INC_H