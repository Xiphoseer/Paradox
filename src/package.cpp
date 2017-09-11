#include "package.hpp"

#include <fstream>
#include <iostream>
#include <cstring>

void PackageInfo::loadFromFile(std::string filename)
{
	std::ifstream infile(filename);
	if (!infile.is_open())
	{
		std::cerr << "Error loading: " << filename << std::endl;
		return;
	}

	infile.seekg(-8, infile.end);

	uint32_t dataAddr, unknown;
	infile.read((char*) &dataAddr, 4);
	infile.read((char*) &unknown, 4); // version?

	infile.seekg(dataAddr, infile.beg);
	this->loadFromStream(infile);

	infile.close();
}

void PackageInfo::loadFromStream(std::istream& input)
{	
	uint32_t count;
	input.read((char*) &count, 4);
	this->files.reserve(count);

	for (int i = 0; i < count; i++)
	{
		PackageInfoEntry entry;

		input.read((char*) &entry.crc, 4);
		input.read((char*) &entry.iLeft, 4);
		input.read((char*) &entry.iRight, 4);
		input.read((char*) &entry.iUncompressedSize, 4);
		input.read((char*) entry.chkUncompressed, 36);
		input.read((char*) &entry.iCompressedSize, 4);
		input.read((char*) entry.chkCompressed, 36);
		input.read((char*) &entry.uDataAddress, 4);
		input.read((char*) &entry.bCompressed, 4);

		this->files.push_back(entry);
	}
}

void PackageInfo::saveToStream(std::ostream& output)
{
	uint32_t count = this->files.size();
	output.write((char*) &count, 4);

	for (int i = 0; i < count; i++)
	{
		PackageInfoEntry entry = this->files.at(i);
		output.write((char*) &entry.crc, 4);
		output.write((char*) &entry.iLeft, 4);
		output.write((char*) &entry.iRight, 4);
		output.write((char*) &entry.iUncompressedSize, 4);
		output.write((char*) entry.chkUncompressed, 36);
		output.write((char*) &entry.iCompressedSize, 4);
		output.write((char*) entry.chkCompressed, 36);
		output.write((char*) &entry.uDataAddress, 4);
		output.write((char*) &entry.bCompressed, 4);
	}
}

PackagePointer::PackagePointer(PackageInfo* package, int32_t index) : package(package)
{
	this->entry = package->files.at(index);
}

PackagePointer::PackagePointer(PackageInfo* package) : package(package)
{
	int32_t size = package->files.size();
	if (size > 0)
	{
		this->entry = package->files.at(size / 2);
	}
}

PackagePointer::PackagePointer() : package(nullptr)
{
	this->entry.iLeft = -1;
	this->entry.iRight = -1;
}

bool PackagePointer::valid()
{
	return (this->package != nullptr) && (this->package->files.size() > 0);
}

uint32_t PackagePointer::crc()
{
	return this->entry.crc;
}

PackagePointer PackagePointer::left()
{
	int32_t index = this->entry.iLeft;
	return (index == -1) ? PackagePointer() : PackagePointer(this->package, index);
}

PackagePointer PackagePointer::right()
{
	int32_t index = this->entry.iRight;
	return (index == -1) ? PackagePointer() : PackagePointer(this->package, index);
}

void PackagePointer::chkUncompressed(char* buffer)
{
	strcpy(buffer, this->entry.chkUncompressed);
}

void PackagePointer::chkCompressed(char* buffer)
{
	strcpy(buffer, this->entry.chkCompressed);
}

uint32_t PackagePointer::uncompressedSize()
{
	return this->entry.iUncompressedSize;
}

uint32_t PackagePointer::compressedSize()
{
	return this->entry.iCompressedSize;
}

uint32_t PackagePointer::dataAddress()
{
	return this->entry.uDataAddress;
}

bool PackagePointer::compressed()
{
	// TODO: is the compressed the same as the data in pki?
	return (this->entry.bCompressed & 0xFF) != 0;
}

PackagePointer findByCRC(PackageInfo* package, uint32_t crc)
{
	PackagePointer ptr(package);
	while (ptr.valid() && ptr.crc() != crc) {
		ptr = (crc > ptr.crc()) ? ptr.right() : ptr.left();
	}
	return ptr;
}