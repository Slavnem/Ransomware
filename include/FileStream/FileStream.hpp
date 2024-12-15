// Slavnem @2024-12-15 Debian 12
// File Stream
#ifndef FILESTREAM_INC_H
#define FILESTREAM_INC_H

#include <iostream>

// Factory Design Pattern
// FileStream::FileStream
namespace FileStream
{
	enum FileOpenType
	{
		EFILEOPEN_WRITE = 0xA, // 10
		EFILEOPEN_WRITEBIN,
		EFILEOPEN_WRITEREAD,
		EFILEOPEN_WRITEREADBIN,

		EFILEOPEN_READ = 0x14, // 20
		EFILEOPEN_READBIN,
		EFILEOPEN_READWRITE,
		EFILEOPEN_READWRITEBIN,

		EFILEOPEN_ADD = 0x1E, // 30
		EFILEOPEN_ADDBIN,
		EFILEOPEN_ADDREAD,
		EFILEOPEN_ADDREADBIN
	};

	// FileStream::FileStream
	class FileStream
	{
		public:;
			virtual void write(const std::string& _text) = 0;
			virtual void close() = 0;
			virtual void print() const = 0;
	};
}

#endif // FILESTREAM_INC_H