#include "pack.hpp"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstring>

#include "catalog.hpp"
#include "package.hpp"

#define CRC_POLY 0x04C11DB7
#define CRC_INIT 0xFFFFFFFF
#define CRC_FXOR 0x00000000


/**
 * The installation directory used
 */
std::string installDir = "./";

/**
 *	The catalog for the current directory
 */
CatalogFile catalog;

/**
 *	Updates a CRC value for the next byte
 */
void updateCRC(uint32_t& crc, uint8_t b)
{
	crc ^= (uint32_t) (b << 24); /* Move byte to MSB */
	for (int i = 0; i < 8; i++)
	{
		if ((crc & 0x80000000) == 0)
		{
			crc <<= 1;
		}
		else
		{
			crc = (uint32_t) ((crc << 1) ^ CRC_POLY);
		}
	}
}

/**
 * Calculates a variation of CRC-32 on a null-terminated string.
 */
uint32_t calculateCRC(const char* path)
{
	uint32_t crc = CRC_INIT;
	/* Process the actual string */
	for (int i = 0; path[i] != 0; i++)
	{
		/* Perform some cleanup on the input */
		uint8_t b = (uint8_t) path[i];
		if (b == '/') b = '\\';
		if ('A' <= b && b <= 'Z') b += ('a' - 'A');

		updateCRC(crc, b);
	}
	/* I have no clue why this was added */
	for (int i = 0; i < 4; i++)
	{
		updateCRC(crc, 0);
	}
	crc ^= CRC_FXOR;
	return crc;
}

/**
 *	Generates a CRC-32 value for the specified filename
 */
uint32_t pack::GetCRCForFilename(const char* filename)
{
	return calculateCRC(filename);
}

/**
 *	Sets the installation directory
 */
int32_t pack::SetInstallDir(char* strDirectory)
{
	installDir = std::string(strDirectory);

	/* We don't know what this is supposed to return */
	return 0;
}

/**
 *	Gets the index of the pack file, which the file in this CRC sits in.
 */
int32_t pack::GetPackIndex(uint32_t filenameCRC)
{
	CatalogPointer ptr = findByCRC(&catalog, filenameCRC);
	if (ptr.valid()) {
		return ptr.packId();
	}
	return -1;
}

int32_t pack::GetInfoForFile(uint32_t filenameCRC, int32_t packIndex, int32_t* bExists, int32_t* iUncompressedSize, char* uncompressedChecksum)
{
	std::string packName = catalog.packFiles.at(packIndex);
	std::replace(packName.begin(), packName.end(), '\\', '/');
	PackageInfo packInfo;
	packInfo.loadFromFile(installDir + packName);

	PackagePointer ptr = findByCRC(&packInfo, filenameCRC);
	if (ptr.valid())
	{
		*bExists = 1;
		*iUncompressedSize = ptr.uncompressedSize();
		ptr.chkUncompressed(uncompressedChecksum);
	}
	else
	{
		*bExists = 0;
	}

	return 0;
}

int32_t pack::MoveFileToPack
(
	char* strFullFilename, char* strManifestFilename,
	int32_t iUncompressedSize, int32_t iCompressedSize,
	char* chkUncompressed, char* chkCompressed,
	int32_t fileIsCompressed
)
{
	uint32_t crc = GetCRCForFilename(strManifestFilename);
	int32_t packIndex = GetPackIndex(crc);
	std::string packFile = catalog.packFiles.at(packIndex);

	std::fstream infile(installDir + packFile);
	if (infile.is_open())
	{
		infile.seekg(-8, infile.end);
		uint32_t dataAddr, unknown;
		infile.read((char*) dataAddr, 4);
		infile.read((char*) unknown, 4);
		infile.seekg(dataAddr, infile.beg);

		PackageInfo info;
		info.loadFromStream(infile);

		infile.seekp(dataAddr, infile.beg);
		info.saveToStream(infile);

		infile.write((char*) dataAddr, 4);
		infile.write((char*) unknown, 4);
	}

	return 0;
}

int32_t pack::ReadPackCatalog(const char* strPackCatalogName)
{
	catalog.loadFromFile(strPackCatalogName);
	return catalog.packFiles.size();
}

int32_t pack::GetPackName(int32_t index, char* buffer, int32_t bufferLenght)
{
	if (index < catalog.packFiles.size())
	{
		std::string name = catalog.packFiles.at(index);
		strcpy(buffer, name.c_str());
		return 0;
	}
	return 1;
}