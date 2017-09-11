#pragma once

#include <iostream>

template<typename T>
class closebuf_basic_istream : public std::basic_istream<T> {
public:
	closebuf_basic_istream(std::streambuf* sb) : std::basic_istream<T>(sb){};
	~closebuf_basic_istream() {
		delete this->rdbuf();
	}
};

typedef closebuf_basic_istream<char> closebuf_istream;
typedef closebuf_basic_istream<wchar_t> closebuf_iwstream;

template<typename T>
class closebuf_basic_ostream : public std::basic_ostream<T> {
public:
	closebuf_basic_ostream(std::streambuf* sb) : std::basic_ostream<T>(sb){};
	~closebuf_basic_ostream() {
		delete this->rdbuf();
	}
};

typedef closebuf_basic_ostream<char> closebuf_ostream;
typedef closebuf_basic_ostream<wchar_t> closebuf_owstream;


template<std::size_t SIZE>
class dump_istreambuf : public std::streambuf {

	char buffer[SIZE];
	std::istream* wrapped;
	std::ofstream* out;

public:
	dump_istreambuf(std::istream* wrapped, std::string file) : wrapped(wrapped) {

		std::cerr << "ST" << std::endl;

		// Create the output stream
		out = new std::ofstream(file, std::ios::binary);

		// Initialize empty buffer
		setg((char*) &buffer, (char*) &buffer, (char*) &buffer);

	}

	~dump_istreambuf() {
		out->close();
		delete out;
	}

	int_type underflow() {

		wrapped->read(buffer, SIZE);
		if (wrapped->eof()) {

			std::size_t len = wrapped->gcount();
			out->write(buffer, len);
			setg((char*) &buffer, (char*) &buffer, (char*) &buffer + len);
			return std::char_traits<char>::eof();
		}

		out->write(buffer, SIZE);
		setg((char*) &buffer, (char*) &buffer, (char*) &buffer + SIZE);
		return std::char_traits<char>::to_int_type(*gptr());

	}

};
