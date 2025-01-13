/***********************************************
 * Project Name     : C Language File System
 * Author           : Slavnem
 * Date             : 15/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : A file handler class developed using the
					  file handling structure of the C language
 ***********************************************/
#include <iostream>
#include <string>
#include <cstdio>
#include <new>

#include <FileStream/FileStream.hpp>
#include <FileStream/CFile/CFile.hpp>
#include <Crypt/Crypt.hpp>
#include <Exception/Exception.hpp>

// FileStream::CFile
namespace FileStream
{
	namespace CFile
	{
		// flag
		static inline constexpr uint8_t CFILE_FLAG_NULL = (0 << 0);
		static inline constexpr uint8_t CFILE_FLAG_OPEN = (1 << 0);
		static inline constexpr uint8_t CFILE_FLAG_CLOSED = (1 << 1);
		static inline constexpr uint8_t CFILE_FLAG_ERR = (1 << 2);
		static inline constexpr uint8_t CFILE_FLAG_WRITABLE = (1 << 3);
		static inline constexpr uint8_t CFILE_FLAG_READABLE = (1 << 4);

		// mode
		static inline constexpr const char* const FILE_MODE_NULL = "";

		static inline constexpr const char* const FILE_MODE_WRITE = "w";
		static inline constexpr const char* const FILE_MODE_WRITEBIN = "wb";
		static inline constexpr const char* const FILE_MODE_WRITEREAD = "w+";
		static inline constexpr const char* const FILE_MODE_WRITEREADBIN = "wb+";

		static inline constexpr const char* const FILE_MODE_READ = "r";
		static inline constexpr const char* const FILE_MODE_READBIN = "rb";
		static inline constexpr const char* const FILE_MODE_READWRITE = "r+";
		static inline constexpr const char* const FILE_MODE_READWRITEBIN = "rb+";

		static inline constexpr const char* const FILE_MODE_ADD = "a";
		static inline constexpr const char* const FILE_MODE_ADDBIN = "ab";
		static inline constexpr const char* const FILE_MODE_ADDREAD = "a+";
		static inline constexpr const char* const FILE_MODE_ADDREADBIN = "ab+";

		// buffer size
		static inline constexpr size_t BUFFER_SIZE = 4096;

		// buffer
		static inline std::string buffer("", BUFFER_SIZE);

		// isPathValid
		bool isPathValid(const std::string& _path)
		{
			return (!_path.empty() && _path.length() > 0);
		}

		// constructor
		CFile::CFile(const std::string& _filepath, const fileopentype_t _opentype)
			: opentype(EFILEOPEN_NULL),
			path(""),
			file(nullptr),
			flag(CFILE_FLAG_ERR)
		{
			if (!isPathValid(_filepath))
				throw Exception::Basic("[CFile] Filepath is not valid");

			setPath(_filepath);
			setFile(_opentype);

			// file validation
			if (!hasFile())
				throw Exception::Critical("[CFile] File could not open");

			// reset the flag
			resetFlag();
		}

		// destructor
		CFile::~CFile()
		{
			closeFile();
		}

		// hasPath
		bool CFile::hasPath() const
		{
			return isPathValid(this->path);
		}

		// hasFile
		bool CFile::hasFile() const
		{
			return (file != nullptr);
		}

		// isReadable
		bool CFile::isReadable() const
		{
			return (flag & CFILE_FLAG_READABLE);
		}

		// isWritable
		bool CFile::isWritable() const
		{
			return (flag & CFILE_FLAG_WRITABLE);
		}

		// isErr
		bool CFile::isErr() const
		{
			return (flag & CFILE_FLAG_ERR);
		}

		// setPath
		void CFile::setPath(const std::string& _filepath)
		{
			path = (!_filepath.empty() ? _filepath : "");
		}

		// setFile
		void CFile::setFile(const fileopentype_t _opentype)
		{
			// filepath validation
			if (!hasPath())
			{
				resetFlag();
				setFlag(CFILE_FLAG_ERR);

				throw Exception::Basic("[CFile:SetFile] File path length can be min " + std::to_string(FILE_PATH_LEN_MIN) + " letter");
			}

			// file open type control
			std::string mode;

			switch (_opentype)
			{
				case EFILEOPEN_READ:  // only read
					mode = FILE_MODE_READ;
					break;
				// case EFILEOPEN_READBIN:  // only read (binary)
					mode = FILE_MODE_READBIN;
					break;
				case EFILEOPEN_READWRITE:  // read and write
					mode = FILE_MODE_READWRITE;
					break;
				// case EFILEOPEN_READWRITEBIN:  // read and write (binary)
					mode = FILE_MODE_READWRITEBIN;
					break;
				case EFILEOPEN_WRITE:  // only write
					mode = FILE_MODE_WRITE;
					break;
				// case EFILEOPEN_WRITEBIN:  // only write (binary)
					mode = FILE_MODE_WRITEBIN;
					break;
				case EFILEOPEN_WRITEREAD:  // write and read
					mode = FILE_MODE_WRITEREAD;
					break;
				// case EFILEOPEN_WRITEREADBIN:  // write and read (binary)
					mode = FILE_MODE_WRITEREADBIN;
					break;
				case EFILEOPEN_ADD:  // only add
					mode = FILE_MODE_ADD;
					break;
				// case EFILEOPEN_ADDBIN:  // only add (binary)
					mode = FILE_MODE_ADDBIN;
					break;
				case EFILEOPEN_ADDREAD:  // add and read
					mode = FILE_MODE_ADDREAD;
					break;
				// case EFILEOPEN_ADDREADBIN:  // add and read (binary)
					mode = FILE_MODE_ADDREADBIN;
					break;
				default:
					resetFlag();
					setFlag(CFILE_FLAG_ERR);

					throw Exception::Basic("[CFile:SetFile] Unsupported file open type");
			}

			// Windows x86/64
			#if defined(_WIN32) || defined(_WIN64) // SECURE
				if (fopen_s(&file, getPath().c_str(), mode.c_str()) != 0)
					file = nullptr;
			// Linux x86/64
			#else // NON SECURE
				if ((file = fopen(getPath().c_str(), mode.c_str())) == nullptr)
					file = nullptr;
			#endif

			// file validation
			if (!hasFile())
				throw Exception::Basic("[CFile:SetFile] File could not open, check if the file exists");

			// set flag
			switch (_opentype)
			{
				// both
				case EFILEOPEN_WRITEREAD:
				// case EFILEOPEN_WRITEREADBIN:
				case EFILEOPEN_ADDREAD:
				// case EFILEOPEN_ADDREADBIN:
				case EFILEOPEN_READWRITE:
				// case EFILEOPEN_READWRITEBIN:
					setFlag(CFILE_FLAG_OPEN);
					setFlag(CFILE_FLAG_READABLE);
					setFlag(CFILE_FLAG_WRITABLE);
					break;

				// only readable
				case EFILEOPEN_READ:
				// case EFILEOPEN_READBIN:
					setFlag(CFILE_FLAG_OPEN);
					setFlag(CFILE_FLAG_READABLE);
					break;

				// only writable
				case EFILEOPEN_WRITE:
				// case EFILEOPEN_WRITEBIN:
				case EFILEOPEN_ADD:
				// case EFILEOPEN_ADDBIN:
					setFlag(CFILE_FLAG_OPEN);
					setFlag(CFILE_FLAG_WRITABLE);
					break;

				// null
				case EFILEOPEN_NULL:
				default:
					resetFlag();
			}
		}

		// getPath
		const std::string& CFile::getPath() const
		{
			return path;
		}

		// getFile
		const FILE* CFile::getFile()
		{
			return file;
		}

		// getFlag
		uint8_t CFile::getFlag() const
		{
			return flag;
		}

		// setFlag
		void CFile::setFlag(const uint8_t _flag)
		{
			flag |= _flag;
		}

		// resetFlag
		void CFile::resetFlag()
		{
			flag = CFILE_FLAG_NULL;
		}

		// removeFlag
		void CFile::removeFlag(const uint8_t _flag)
		{
			flag &= ~_flag;
		}

		// readLine
		std::string* CFile::readLine(const bool _setoldpos)
		{
			// check the if file is exist
			if (!hasFile())
				throw Exception::Critical("[CFile:ReadLine] A file must exist to be readable");

			// file pos
			long currentFilePos = ftell(file);

			// temporarily read and save data
			char temp[BUFFER_SIZE];
			if (!fgets(temp, BUFFER_SIZE, file))
				return nullptr;

			// assign data to buffer
			buffer.assign(temp);

			// set the old pos
			if(_setoldpos)
				fseek(file, currentFilePos, SEEK_SET);

			// changeable text
			return &buffer;
		}

		// writeLine
		bool CFile::writeLine(const std::string* _text)
		{
			// file not found
			if (!hasFile())
				throw Exception::Critical("[CFile:WriteLine] A file must exist to be writable");

			// check the ptr
			if (!_text || _text->empty())
				return false;

			// write and don't cache
			// Windows x86/64
			#if defined(_WIN32) || defined(_WIN64) // SECURE
				if (fprintf_s(file, "%s", _text->data()) < 0)
					return false;
			// Linux x86/64
			#else // NON SECURE
				if(fprintf(file, "%s", _text->data()) < 0)
					return false;
			#endif

			// write data directly to file without saving to buffer
			return (fflush(file) == 0);
		}

		// nextLine
		bool CFile::nextLine()
		{
			// file not found
			if (!hasFile())
				throw Exception::Critical("[CFile:NextLine] A file must exist to go nextline");

			// temporarily read data for nextline
			char temp[BUFFER_SIZE];
			return (fgets(temp, BUFFER_SIZE, file));
		}

		// closeFile
		void CFile::closeFile()
		{
			// file already closed
			if (!hasFile())
				throw Exception::Message("[CFile:CloseFile] File already closed :)");

			// close the file
			fclose(file);
			file = nullptr;
		}

		// print
		void CFile::print() const
		{
			// We output encryption type, key, encryption status, decryption status
			std::cout << "\n========== CFILE =========="
				<< "\nPath: " << (this->getPath().data())
				<< "\nOpen: " << ((this->isReadable() || this->isWritable()) ? "Yes" : "No")
				<< "\nReadable: " << (this->isReadable() ? "Yes" : "No")
				<< "\nWritable: " << (this->isWritable() ? "Yes" : "No")
				<< "\nError: " << (this->isErr() ? "Yes" : "No")
				<< std::endl;
		}
	}
}