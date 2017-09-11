#pragma once

#include <fstream>
#include <zlib.h>
#include "stream.hpp"

/* This class provides an input stream buffer that
 * allows on-the-fly decompression of zlib streams
 * within the input stream pipeline.
 */
template<std::size_t SIZE>
class zlib_istreambuf: public std::streambuf {
	
	std::istream *input;	// The input stream to read from
	char ibuf[SIZE];		// The internal input buffer
	char obuf[SIZE];		// The internal output buffer
	
	z_stream c_stream;		// The stream for decompression
	int err;				// The error state

public:

	using Base = std::streambuf;
	using char_type = Base::char_type;
	using int_type = Base::int_type;

	// Constructor for this stream buffer
	zlib_istreambuf(std::istream *input) : input(input) {
		
		// Set functions that the stream may use
		c_stream.zalloc = (alloc_func) 0;
	    c_stream.zfree = (free_func) 0;
	    c_stream.opaque = (voidpf) 0;

	    // Initialize z_stream pointers
	    c_stream.avail_in = 0;
	    c_stream.avail_out = SIZE;

	    // Initialize the inflating
	    err = inflateInit(&c_stream);
	    
	    // Set badbit when stream is not ok
	    if (err != Z_OK) {
	    	
	    	// setstate(std::ios_base::badbit);
	    	return;
	    }

	    // Set the input buffer as full
	    setg((char*) &obuf,(char*) &obuf+SIZE,(char*) &obuf+SIZE);
	}

	~zlib_istreambuf(){
		inflateEnd(&c_stream);
	}

	// The underflow function for refilling the buffer
	int_type underflow() {

		// Check whether we have no more data to inflate
		if (c_stream.avail_out != 0) {

			// Fill the buffer
			input->read(ibuf, SIZE);
			int_type len = input->eof() ? input->gcount() : SIZE;

			// When nothing was read, end of file
			if (len == 0) {

				// Clean up the stream
				inflateEnd(&c_stream);
				return std::char_traits<char>::eof();
			}
			
			// Set the input for the zlib stream
			c_stream.avail_in = len;
			c_stream.next_in = (unsigned char*) &ibuf;
		}

		// Set the outbut buffer for the zlib stream
		c_stream.avail_out = SIZE;
		c_stream.next_out = (unsigned char*) &obuf;

		// Inflate and update streambuf pointers
		err = inflate(&c_stream, Z_FINISH);
		int have = SIZE - c_stream.avail_out;

		// Set the new pointers
		setg((char*) &obuf, (char*) &obuf, (char*) &obuf+have);

		if (have == 0) return underflow();

		// When nothing has been written
		/*if (c_stream.avail_out == SIZE) {

			std::cerr << "This CASE " << have << std::endl;

			// Clean up the stream
			inflateEnd(&c_stream);
			return std::char_traits<char>::eof();
		}*/

		// Return the next available character
		return std::char_traits<char>::to_int_type(*gptr());
	}
};

template<std::size_t SIZE>
std::istream* create_inflate_stream(std::istream* in) {
	return new closebuf_istream(new zlib_istreambuf<SIZE>(in));
}
