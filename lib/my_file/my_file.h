#ifndef MY_FILE_H
#define MY_FILE_H


#include <fstream>

class MyException : public std::exception
{
	private:
	const char* msg;

	public:
		MyException(const char* msg_);
		virtual ~MyException();

		const char* what() const noexcept override;
};

// MyFile object builded, if has file at path_
// or set default argument isRw_=true.
// Raw dynamic char array in class has default arg segment_=1024
// for new array created and increments size array.
class MyFile
{
	private:
		const unsigned int segment;
		const char* path;
		std::ifstream fin;
		std::ofstream fout;
		char* data;
		const char* data_str;
		std::string str;
		unsigned int size;
		bool isRw;

		void data_resize(int i);
		void read();
		void write();

	public:
		MyFile(const char* path_, std::string str_="", const unsigned int segment_ = 1024);
		virtual ~MyFile();
	
		std::string to_str(const char divider = ' ');
};

#endif