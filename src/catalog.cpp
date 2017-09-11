#include "catalog.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>


int CatalogFile::loadFromFile(std::string filename)
{
	std::ifstream infile(filename);
	if (infile.is_open())
	{
		this->loadFromStream(infile);
		infile.close();
		return 0;
	}
	else
	{
		std::cerr << "Failed to load '" << filename << "' as catalog!" << std::endl;
		return 1;
	}
	
}

int CatalogFile::loadFromStream(std::istream& input)
{
	/* Clean up the fields */
	this->packFiles.clear();
	this->files.clear();

	/* Load the version */
	input.read((char*) &(this->version), 4);
	
	/* Load the list of pack files */
	uint32_t pkFileCount;
	input.read((char*) &pkFileCount, 4);
	this->packFiles.reserve(pkFileCount);

	for (int i = 0; i < pkFileCount; i++)
	{
		uint32_t len;
		input.read((char*) &len, 4);

		char buf[len];
		input.read(buf, len);

		std::string name(buf, len);
		this->packFiles.push_back(name);
	}

	/* Load the list of packed files */
	uint32_t filesCount;
	input.read((char*) &filesCount, 4);
	this->files.reserve(filesCount);

	for (int i = 0; i < filesCount; i++)
	{
		CatalogEntry entry;
		input.read((char*) &entry.crc, 4);
		input.read((char*) &entry.left, 4);
		input.read((char*) &entry.right, 4);
		input.read((char*) &entry.pack, 4);
		input.read((char*) &entry.data, 4);

		this->files.push_back(entry);
	}
}

/*
 * Returns the pack-index for a given pack file name
 */
int CatalogFile::getPackIndex(std::string packName)
{
	/* Sanitize input */
	std::replace(packName.begin(), packName.end(), '/', '\\');
	
	for (int i = 0; i < this->packFiles.size(); i++)
	{
		if (packFiles.at(i) == packName) return i;
	}
	return -1;
}

CatalogPointer::CatalogPointer(CatalogFile* file)
{
	if (file->files.size() > 0)
	{
		int32_t root = file->files.size() / 2;
		this->file = file;
		this->entry = file->files.at(root);	
	}
	else
	{
		this->file = nullptr;
	}
	
}

CatalogPointer::CatalogPointer(CatalogFile* file, int32_t index) : file(file)
{
	this->entry = file->files.at(index);
}

CatalogPointer::CatalogPointer()
{
	this->file = nullptr;
	this->entry = CatalogEntry();
}

bool CatalogPointer::valid() {
	return this->file != nullptr;
}

uint32_t CatalogPointer::crc() {
	return this->entry.crc;
}

CatalogPointer CatalogPointer::left() {
	int32_t id = this->entry.left;
	return (id == -1) ? CatalogPointer() : CatalogPointer(this->file, id);
}

CatalogPointer CatalogPointer::right() {
	int32_t id = this->entry.right;
	return (id == -1) ? CatalogPointer() : CatalogPointer(this->file, id);
}

std::string CatalogPointer::pack() {
	return this->file->packFiles.at(this->entry.pack);
}

uint32_t CatalogPointer::data() {
	return this->entry.data;
}

int32_t CatalogPointer::packId() {
	return this->entry.pack;
}

CatalogPointer findByCRC(CatalogFile* file, uint32_t crc)
{
	CatalogPointer ptr(file);
	while (ptr.valid() && ptr.crc() != crc) {
		ptr = (crc > ptr.crc()) ? ptr.right() : ptr.left();
	}
	return ptr;
}
