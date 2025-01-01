// Slavnem @2024-12-15
// FileStream
#ifndef FILESTREAM_INC_H
#define FILESTREAM_INC_H

// Factory Design Pattern
// FileStream
namespace FileStream
{
	typedef enum fileopentype_s
	{
		EFILEOPEN_NULL = 0x0, // 0

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
	} fileopentype_t;

	// FileStream::FileStream
	template<typename fileT, typename inputT, typename outputT>
	class FileStream
	{
		private:
			fileopentype_t opentype;
			inputT path;
			fileT file;

			// set
			virtual void setPath(inputT&) = 0;
			virtual void setFile(const fileopentype_t) = 0;

		public:
			// has validation
			virtual bool hasPath() const = 0;
			virtual bool hasFile() const = 0;

			// is validation
			virtual bool isErr() const = 0;

			// get
			virtual outputT getPath() const = 0;
			virtual fileT* getFile() = 0;

			// abstract
			virtual void write(const inputT&) = 0;
			virtual outputT read() = 0;
			virtual void close() = 0;
			virtual void print() const = 0;
	};
}

#endif // FILESTREAM_INC_H