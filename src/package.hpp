#pragma once

#include <istream>
#include <ostream>
#include <vector>
#include <string>

struct PackageInfoEntry
{
	uint32_t crc;
	int32_t iLeft;
	int32_t iRight;
	int32_t iUncompressedSize;
	char chkUncompressed[36];
	int32_t iCompressedSize;
	char chkCompressed[36];
	uint32_t uDataAddress;
	uint32_t bCompressed;
};

struct PackageInfo
{
	std::vector<PackageInfoEntry> files;

	void loadFromFile(std::string filename);
	void loadFromStream(std::istream& input);
	void saveToStream(std::ostream& output);
};

class PackagePointer
{
	PackageInfo* package;
	PackageInfoEntry entry;
	PackagePointer(PackageInfo* package, int32_t index);
	PackagePointer();
public:

	PackagePointer(PackageInfo* package);
	bool valid();
	uint32_t crc();
	PackagePointer left();
	PackagePointer right();
	void chkCompressed(char* buffer);
	void chkUncompressed(char* buffer);
	uint32_t uncompressedSize();
	uint32_t compressedSize();
	uint32_t dataAddress();
	bool compressed();
};

PackagePointer findByCRC(PackageInfo* package, uint32_t crc);