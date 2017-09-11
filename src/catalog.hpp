#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <istream>


/**
 *	One entry within a catalog file
 */
struct CatalogEntry
{
	uint32_t crc;	/* The CRC-32 value for the filename */
	int32_t left;	/* The left child of this node */
	int32_t right;	/* The right child of this node */
	int32_t pack;	/* The index of the pack that this entry contains */
	uint32_t data;	/* Additional data, possibly a category or gating id */
};

/**
 *	A catalog file such as 'versions/primary.pki'
 */
struct CatalogFile
{
	std::vector<std::string> packFiles;
	std::vector<CatalogEntry> files;
	uint32_t version;

	int loadFromFile(std::string filename);
	int loadFromStream(std::istream& file);
	int getPackIndex(std::string packName);
};

/**
 *	Helper class to make walking through the catalog
 *	easier by interpreting the entry values on the fly.
 */
class CatalogPointer
{
private:
	CatalogEntry entry;
	CatalogFile* file;
	CatalogPointer(CatalogFile* file, int32_t index);
	CatalogPointer();
	
public:
	CatalogPointer(CatalogFile* file);
	bool valid();

	uint32_t crc();
	CatalogPointer left();
	CatalogPointer right();
	std::string pack();
	int32_t packId();
	uint32_t data();
};

CatalogPointer findByCRC(CatalogFile* file, uint32_t crc);