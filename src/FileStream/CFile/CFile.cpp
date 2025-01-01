// Slavnem @2024-12-15
// CFile Src

#include <iostream>
#include <string>
#include <cstdio>
#include <new>

#include <FileStream/FileStream.hpp>
#include <FileStream/CFile/CFile.hpp>

// FileStream::CFile
namespace FileStream
{
	namespace CFile
	{
		// flag
		static inline constexpr uint8_t FILE_FLAG_NULL = (0 << 0);
		static inline constexpr uint8_t FILE_FLAG_OPEN = (1 << 0);
		static inline constexpr uint8_t FILE_FLAG_CLOSED = (1 << 1);
		static inline constexpr uint8_t FILE_FLAG_ERROR = (1 << 2);
		static inline constexpr uint8_t FILE_FLAG_WRITABLE = (1 << 3);
		static inline constexpr uint8_t FILE_FLAG_READABLE = (1 << 4);

		// max & min
		static inline constexpr uint32_t PATH_LEN_MIN = 1;
		static inline constexpr uint32_t PATH_LEN_MAX = UINT32_MAX;

		// buffer
		static inline constexpr uint16_t BUFFER_SIZE = 512;

		// constructor
		CFile::CFile(std::string& _filepath, const fileopentype_t _opentype)
			: opentype(EFILEOPEN_NULL),
			path(""),
			file(nullptr),
			flag(FILE_FLAG_ERROR)
		{
			setPath(_filepath);
			setFile(_opentype);

			// file validation
			if (!hasFile())
			{
				// throw msg handler
				std::cerr << "[FileStream::CFile] File Not Opened" << std::endl;
				return;
			}

			// reset the flag
			resetFlag();
		}

		// hasPath
		bool CFile::hasPath() const
		{
			return !path.empty();
		}

		// hasFile
		bool CFile::hasFile() const
		{
			return file != nullptr;
		}

		// isErr
		bool CFile::isErr() const
		{
			return (flag & FILE_FLAG_ERROR);
		}

		// setPath
		void CFile::setPath(std::string& _filepath)
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
				setFlag(FILE_FLAG_ERROR);

				std::cerr << "[FileStream::CFile::SetFile] File Path Length Can Be Min"
					<< static_cast<int>(PATH_LEN_MIN) << " Letter"
					<< std::endl;

				return;
			}

			// file open type control
			std::string mode;

			switch (_opentype)
			{
				case EFILEOPEN_READ:  // only read
					mode = "r";
					break;
				case EFILEOPEN_READBIN:  // only read (binary)
					mode = "rb";
					break;
				case EFILEOPEN_READWRITE:  // read and write
					mode = "r+";
					break;
				case EFILEOPEN_READWRITEBIN:  // read and write (binary)
					mode = "rb+";
					break;
				case EFILEOPEN_WRITE:  // only write
					mode = "w";
					break;
				case EFILEOPEN_WRITEBIN:  // only write (binary)
					mode = "wb";
					break;
				case EFILEOPEN_WRITEREAD:  // write and read
					mode = "w+";
					break;
				case EFILEOPEN_WRITEREADBIN:  // write and read (binary)
					mode = "wb+";
					break;
				case EFILEOPEN_ADD:  // only add
					mode = "a";
					break;
				case EFILEOPEN_ADDBIN:  // only add (binary)
					mode = "ab";
					break;
				case EFILEOPEN_ADDREAD:  // add and read
					mode = "a+";
					break;
				case EFILEOPEN_ADDREADBIN:  // add and read (binary)
					mode = "ab+";
					break;
				default:
					resetFlag();
					setFlag(FILE_FLAG_ERROR);

					std::cerr << "[FileStream::CFile::SetFile] File Couldn't Open, Check The File Exist" << std::endl;
					return;
			}

			// Windows x86/64
			#if defined(_WIN32) || defined(_WIN64) // SECURE
				if (fopen_s(&file, getPath(), mode.c_str()) != 0)
					file = nullptr;
			// Linux x86/64
			#else // NON SECURE
				if ((file = fopen(getPath(), mode.c_str())) == NULL)
					file = nullptr;
			#endif

			// file validation
			if (!hasFile())
			{
				std::cerr << "[FileStream::CFile::SetFile] File Couldn't Open, Check The File Exist" << std::endl;
				return;
			}

			// set flag
			switch (_opentype)
			{
				// both
				case EFILEOPEN_WRITEREAD:
				case EFILEOPEN_WRITEREADBIN:
				case EFILEOPEN_ADDREAD:
				case EFILEOPEN_ADDREADBIN:
				case EFILEOPEN_READWRITE:
				case EFILEOPEN_READWRITEBIN:
					setFlag(FILE_FLAG_OPEN);
					setFlag(FILE_FLAG_READABLE);
					setFlag(FILE_FLAG_WRITABLE);
					break;

				// only readable
				case EFILEOPEN_READ:
				case EFILEOPEN_READBIN:
					setFlag(FILE_FLAG_OPEN);
					setFlag(FILE_FLAG_READABLE);
					break;

				// only writable
				case EFILEOPEN_WRITE:
				case EFILEOPEN_WRITEBIN:
				case EFILEOPEN_ADD:
				case EFILEOPEN_ADDBIN:
					setFlag(FILE_FLAG_OPEN);
					setFlag(FILE_FLAG_WRITABLE);
					break;

				// null
				case EFILEOPEN_NULL:
				default:
					resetFlag();
			}
		}

		// getPath
		const char* CFile::getPath() const
		{
			return static_cast<const char*>(path.c_str());
		}

		// getFile
		FILE* CFile::getFile()
		{
			return file;
		}

		// write
		void CFile::write(const std::string& _text)
		{
			// file not found
			if (!hasFile())
				return;

			// write and don't cache
			fprintf(file, "%s", _text.c_str());
			fflush(file);
		}

		// read
		const char* CFile::read()
		{
			// check the if file is exist
			if (!hasFile())
			{
				std::cerr << "[FileStream::CFile::Read] A File Must Exist To Be Readable" << std::endl;
				return nullptr;
			}

    		// buffer for reading file line
			char* buffer = nullptr;

			// mem allocation for buffer
			try
			{
				buffer = new char[BUFFER_SIZE];
			}
			catch(...)
			{
				std::cerr << "[FileStream::CFile::Read] Mem Couldn't Alloc For Read Buffer" << std::endl;
				return nullptr;
			}

    		if (fgets(buffer, BUFFER_SIZE, getFile()) == nullptr)
			{
				std::cerr << "[FileStream::CFile::Read] Failed To Read From File" << std::endl;
				return nullptr;
			}

    		// unchangeable text
    		return buffer;
		}

		// close
		void CFile::close()
		{
			// file already closed
			if (!hasFile())
				return;

			fclose(file); // close the file
			file = nullptr;
		}

		// print
		void CFile::print() const
		{
			std::cout << "\n==========" << std::internal << " FILE " << "=========="
				<< "\nPath: " << (hasPath() ? getPath() : "Null")
				<< "\nOpen: " << (hasFile() ? "Yes" : "No")
				<< "\nReadable: " << (hashFlag(FILE_FLAG_READABLE) ? "Yes" : "No")
				<< "\nWritable: " << (hashFlag(FILE_FLAG_WRITABLE) ? "Yes" : "No")
				<< "\nError: " << (hashFlag(FILE_FLAG_ERROR) ? "Yes" : "No")
				<< std::endl;
		}
	}
}