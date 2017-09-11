#pragma once

#include <string>
#include <vector>
#include <istream>

struct ManifestEntry {
	std::string path;
	uint32_t sizeA;
	std::string checkA;
	uint32_t sizeB;
	std::string checkB;
	std::string checkC;
};

struct ManifestFile {
	uint32_t fileVersion;
	std::string checksum;
	std::string version;
	std::vector<ManifestEntry> files;

	int loadFromFile(std::string filename);
	int loadFromStream(std::istream& file);
	ManifestEntry find(std::string path);
};
