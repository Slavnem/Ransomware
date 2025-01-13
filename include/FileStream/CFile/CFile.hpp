/***********************************************
 * Project Name     : C Language File System
 * Author           : Slavnem
 * Date             : 15/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : A file handler class developed using the
					  file handling structure of the C language
 ***********************************************/
#ifndef FILESTREAM_CFILE_INC_H
#define FILESTREAM_CFILE_INC_H

#include <iostream>
#include <cstdio>
#include <string>

#include <FileStream/FileStream.hpp>

// FileStream::CFile
namespace FileStream
{
	namespace CFile
	{
		// is path valid
		bool isPathValid(const std::string& _path);

		class CFile : public FileStream<FILE, std::string, std::string>
		{
			private:
				fileopentype_t opentype;
				std::string path;
				FILE* file;
				uint8_t flag;

				CFile() = default; // block for create new public object

				// set
				virtual void setPath(const std::string& _filepath) override;
				virtual void setFile(const fileopentype_t _opentype) override;

			public:
				// block
				CFile(const CFile&) = delete;

				// constructor
				explicit CFile(const std::string& _filepath, const fileopentype_t _opentype);

				// destructor
				~CFile();

				// has validation
				virtual bool hasPath() const override;
				virtual bool hasFile() const override;

				// is validation
				virtual bool isReadable() const override;
				virtual bool isWritable() const override;
				virtual bool isErr() const override;

				// get
				virtual const std::string& getPath() const override;

				// line
				virtual std::string* readLine(const bool _setoldpos = 0) override;
				virtual bool writeLine(const std::string* _text) override;
				virtual bool nextLine() override;

				// close
				virtual void closeFile() override;

				// print
				virtual void print() const override;

			protected:
				// get file
				virtual const FILE* getFile() override;

				// get, set, reset, remove flag
				virtual uint8_t getFlag() const;
				virtual void setFlag(const uint8_t _flag);
				virtual void resetFlag();
				virtual void removeFlag(const uint8_t _flag);
		};
	}
}

#endif // FILESTREAM_CFILE_INC_H