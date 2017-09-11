#pragma once

#include <fstream>
#include <cassert>
#include <zlib.h>

#include "stream.hpp"

/*
 * This class allows the reading of sd0 compressed files, as
 * by taking such a file and provides just the compressed part of it
 * as the buffer.
 *
 */
template<std::size_t SIZE>
class sd0_istreambuf : public std::streambuf {

	std::istream *input;

	char ibuf[SIZE];			// The internal input buffer
	char obuf[SIZE];			// The internal output buffer
	int32_t block_remain = 0;	// How much bytes remain to be read in the current block
	int32_t block_size = -1;	// How much bytes the current block has

	int32_t block_decomp_size = 0;

	bool fail;
	bool open = false;

	z_stream c_stream;			// The compression stream
	int err;					// The error code

public:
	sd0_istreambuf(std::istream *input) : input(input) {

		block_remain = 0;
		block_size = 0;
		fail = false;
		
		char sm_buf[5];
		char magic_buf[5] = {'s', 'd', '0', 1, -1};
		
		input->read(sm_buf, 5);
		if (input->eof()) {
			fail = true;
			return;
		}

		for (int i = 0; i < 5; i++) {
			if (sm_buf[i] != magic_buf[i]){
				std::cout << "Header not found, abort" << std::endl;
				return;
			}
		}

		// Set functions that the stream may use
		c_stream.zalloc = (alloc_func) 0;
	    c_stream.zfree = (free_func) 0;
	    c_stream.opaque = (voidpf) 0;

	    // Set the initial pointers / values
		c_stream.avail_in = SIZE;
		c_stream.next_in = (Bytef*) &ibuf;
		c_stream.avail_out = SIZE;
		c_stream.next_out = (Bytef*) &obuf;

		// Set the buffer as empty
		setg((char*) &obuf, (char*) &obuf+SIZE, (char*) &obuf+SIZE);
		
	}

	~sd0_istreambuf()
	{
		if (open) inflateEnd(&c_stream);
	}

	int_type underflow()
	{
		// When we have no more output to write
		if (c_stream.avail_out != 0)
		{	
			// When the current block is empty
			if (block_remain == 0)
			{
				// Check the next buffer size
				input->read((char*) &block_size, 4);

				// When the reading failed --> End of file
				if (input->eof())
				{
					//std::cerr << block_decomp_size << std::endl;
					//std::cerr << "EOF!" << std::endl;

					// If not found -> end of file
					return std::char_traits<char>::eof();
				}

				// Set the new block size
				block_remain = block_size;
				// std::cerr << "Size: " << block_size << "!" << std::endl;

				// Close old streams
				if (open)
				{
					//std::cerr << block_decomp_size << std::endl;
					block_decomp_size = 0;
					inflateEnd(&c_stream);
				}

				// Initialize the new stream
				err = inflateInit(&c_stream);
				open = true;
			}

			// Read the next amount of bytes
			int32_t next = block_remain < SIZE ? block_remain : SIZE;
			//std::cerr << "Try read " << next << " characters" << std::endl;
			input->read(ibuf, next);

			int32_t len = input->eof() ? input->gcount() : next;

			// Set the input values
			c_stream.avail_in = len;
			c_stream.next_in = (Bytef*) &ibuf;

			//std::cerr << "Read: " << len << " characters" << std::endl;

			// Update remaining read space
			block_remain -= len;

		}

		c_stream.avail_out = SIZE;
		c_stream.next_out = (Bytef*) &obuf;

		err = inflate(&c_stream, Z_NO_FLUSH);
		int have = SIZE - c_stream.avail_out;

		if (have > 0)
		{	
			block_decomp_size += have;			
			setg((char*) &obuf, (char*) &obuf, (char*) &obuf + have);
			int_type chr = std::char_traits<char>::to_int_type(*gptr());
			
			if (chr == std::char_traits<char>::eof())
			{
				std::cerr << "MISMATCH" << std::endl;
			}

			return chr;
		}
		else return underflow();
	}
};

template<std::size_t SIZE>
std::istream* create_sd0_stream(std::istream* in)
{
	return new closebuf_istream(new sd0_istreambuf<SIZE>(in));
}

template<std::size_t ISIZE, std::size_t OSIZE>
class sd0_ostreambuf : public std::streambuf {

	char ibuf[ISIZE];
	char obuf[ISIZE];

	std::ostream* output;

public:
	sd0_ostreambuf(std::ostream* output) : output(output) {

		char header[5] = {'s', 'd', '0', 1, -1};
		output->write((char*) &header, 5);
		setp((char*) &ibuf, (char*) &ibuf + ISIZE);
	}

	int_type overflow(int_type c) {

		z_stream c_stream;
		c_stream.zalloc = (alloc_func) 0;
	    c_stream.zfree = (free_func) 0;
	    c_stream.opaque = (voidpf) 0;

		deflateInit(&c_stream, 4);

		int32_t len = pptr() - (char*) &ibuf;

		c_stream.avail_in = len;
		c_stream.next_in = (Bytef*) &ibuf;
	
		c_stream.avail_out = ISIZE;
		c_stream.next_out = (Bytef*) &obuf;

		deflate(&c_stream, Z_FINISH);

		int32_t have = ISIZE - c_stream.avail_out;
		if (have > 0) {
			output->write((char*) &have, 4);
			output->write((char*) &obuf, have);
		}

		assert(c_stream.avail_out > 0);

		deflateEnd(&c_stream);
		ibuf[0] = c;
		setp((char*) &ibuf + 1, (char*) &ibuf + ISIZE);

		return traits_type::to_int_type(c);
	}

	int_type sync() {
		this->overflow(0);
		this->output->flush();
	}
};

template<std::size_t SIZE>
std::ostream* create_sd0_ostream(std::ostream* in)
{
	return new closebuf_ostream(new sd0_ostreambuf<262144, SIZE>(in));
}