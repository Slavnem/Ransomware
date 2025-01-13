/***********************************************
 * Project Name     : Virtual File Stream Class
 * Author           : Slavnem
 * Date             : 15/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Virtual File Stream Class
 ***********************************************/
#ifndef FILESTREAM_INC_H
#define FILESTREAM_INC_H

// Factory Design Pattern
// FileStream
namespace FileStream
{
	// max & min
	inline constexpr uint32_t FILE_PATH_LEN_MIN = 1;
	inline constexpr uint32_t FILE_PATH_LEN_MAX = UINT32_MAX;

	typedef enum fileopentype_s
	{
		EFILEOPEN_NULL = 0x0, // 0

		EFILEOPEN_WRITE = 0xA, // 10
		// EFILEOPEN_WRITEBIN,
		EFILEOPEN_WRITEREAD,
		// EFILEOPEN_WRITEREADBIN,

		EFILEOPEN_READ = 0x14, // 20
		// EFILEOPEN_READBIN,
		EFILEOPEN_READWRITE,
		// EFILEOPEN_READWRITEBIN,

		EFILEOPEN_ADD = 0x1E, // 30
		// EFILEOPEN_ADDBIN,
		EFILEOPEN_ADDREAD,
		// EFILEOPEN_ADDREADBIN
	} fileopentype_t;

	template<typename fileT, typename inputT, typename outputT>
	class FileStream
	{
		private:
			fileopentype_t opentype = EFILEOPEN_NULL;
			inputT path;
			fileT file;

			// set
			virtual void setPath(const inputT&) = 0;
			virtual void setFile(const fileopentype_t) = 0;

		public:
			// constructor

			// has validation
			virtual bool hasPath() const = 0;
			virtual bool hasFile() const = 0;

			// is validation
			virtual bool isReadable() const = 0;
			virtual bool isWritable() const = 0;
			virtual bool isErr() const = 0;

			// get
			virtual const inputT& getPath() const = 0;

			// line
			virtual outputT* readLine(const bool = 0) = 0;
			virtual bool writeLine(const inputT*) = 0;
			virtual bool nextLine() = 0;
			
			// close
			virtual void closeFile() = 0;
			
			// print
			virtual void print() const = 0;

		protected:
			virtual const fileT* getFile() = 0;
	};
}

#endif // FILESTREAM_INC_H