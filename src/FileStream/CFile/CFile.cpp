// Slavnem @2024-12-15 Debian 12
// CFile Src

#include <iostream>
#include <string>
#include <cstdio>

#include <FileStream/FileStream.hpp>
#include <FileStream/CFile/CFile.hpp>

// FileStream::CFile
namespace FileStream
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

    // constructor
	CFile::CFile(const std::string& _filepath, const enum FileOpenType _opentype)
		: file(nullptr),
		flag(FILE_FLAG_NULL)
	{
		setOpen(_filepath, _opentype);
	}

	// destructor
	CFile::~CFile()
	{
		// close the file
		close();
	}

    // isOpen
	bool CFile::isOpen() const
	{
		// if file has, it's already open
		return hashFileFlag(FILE_FLAG_OPEN);
	}

    // setOpen
	bool CFile::setOpen(const std::string& _filepath, const enum FileOpenType _opentype)
	{
		// check the filepath length
		if (_filepath.empty())
		{
			resetFileFlag();
			setFileFlag(FILE_FLAG_ERROR);

			std::cerr << "[ERROR] File Path Length Can Be Min 1 Letter!" << std::endl;
			return false;
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
			resetFileFlag();
			setFileFlag(FILE_FLAG_ERROR);

			std::cerr << "[ERROR] No File Opening Type As Entered!" << std::endl;
			return false;
		}

		// try to open file
		if ((file = fopen(_filepath.c_str(), mode.c_str())) == NULL)
		{
			std::cerr << "[ERROR] File Couldn't Open, Check The File Exist!" << std::endl;
			return false;
		}

		// set filepath
		setPath(_filepath);

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
			setFileFlag(FILE_FLAG_OPEN);
			setFileFlag(FILE_FLAG_READABLE);
			setFileFlag(FILE_FLAG_WRITABLE);
				break;

			// only readable
			case EFILEOPEN_READ:
			case EFILEOPEN_READBIN:
			setFileFlag(FILE_FLAG_OPEN);
			setFileFlag(FILE_FLAG_READABLE);
				break;

			// only writable
			case EFILEOPEN_WRITE:
			case EFILEOPEN_WRITEBIN:
			case EFILEOPEN_ADD:
			case EFILEOPEN_ADDBIN:
				setFileFlag(FILE_FLAG_OPEN);
				setFileFlag(FILE_FLAG_WRITABLE);
				break;
		}

		return true;
	}

    // setPath
	void CFile::setPath(const std::string& _filepath)
	{
		path = (_filepath.length() > 0 ? _filepath : "");
	}

	// getFile
	FILE* CFile::getFile()
	{
		return file;
	}

    // getPath
	std::string CFile::getPath() const
	{
		return (path.length() > 0 ? path : "");
	}

	// write
	void CFile::write(const std::string& _text)
	{
		// file not found
		if(!file) return;

		// write and don't cache
		fprintf(file, "%s", _text.c_str());
		fflush(file);
	}

	// close
	void CFile::close()
	{
		// file already closed
		if(!file)
			return;

		fclose(file); // close the file
		file = nullptr;
	}

	// print
	void CFile::print() const
	{
		std::cout << "\n==========" << std::internal << " FILE " << "=========="
			<< "\nPath: " << (path.length() > 0 ? path : "Null")
			<< "\nOpen: " << (isOpen() ? "Yes" : "No")
			<< "\nReadable: " << (hashFileFlag(FILE_FLAG_READABLE) ? "Yes" : "No")
			<< "\nWritable: " << (hashFileFlag(FILE_FLAG_WRITABLE) ? "Yes" : "No")
			<< "\nError: " << (hashFileFlag(FILE_FLAG_ERROR) ? "Yes" : "No")
			<< std::endl;
	}
}