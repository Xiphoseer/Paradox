#pragma once
#include <stdint.h>

namespace pack
{
	int32_t SetInstallDir(char* strDirectory);
	uint32_t GetCRCForFilename(const char* strFilename);
	int32_t GetPackIndex(uint32_t filenameCRC);
	int32_t GetInfoForFile(uint32_t filenameCRC, int32_t packIndex, int32_t* bExists, int32_t* iUncompressedSize, char* uncompressedChecksum);
	int32_t MoveFileToPack(char* strFullFilename, char* strManifestFilename, int32_t iUncompressedSize, int32_t iCompressedSize, char* chkUncompressed, char* chkCompressed, int32_t fileIsCompressed);

	int32_t ReadPackCatalog(const char* strPackCatalogName);

	int32_t GetPackName(int32_t index, char* buffer, int32_t bufferLenght);
}
