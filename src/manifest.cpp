#include "manifest.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

enum ManifestSection {
	MF_GENERAL,
	MF_VERSION,
	MF_FILES,
	MF_UNKNOWN
};

bool lexicalCompare(std::string A, std::string B) {
	return A.compare(B) < 0;
}

bool manifestCompare(ManifestEntry A, ManifestEntry B) {
	return lexicalCompare(A.path, B.path);
}

int ManifestFile::loadFromFile(std::string filename) {
	std::ifstream infile(filename);
	if (infile.is_open())
	{
		this->loadFromStream(infile);
		infile.close();
		return 0;
	}
	else
	{
		std::cerr << "Failed to load '" << filename << "' as manifest!" << std::endl;
		return 1;
	}
}

int ManifestFile::loadFromStream(std::istream& infile) {
	std::string line;

	ManifestSection section = MF_GENERAL;

	while(!infile.eof()){
        std::getline(infile, line);
        
        // Ignore empty lines
        if (line.length() == 0) continue;
        
        // Find INI-like headers "[...]"
        if (line.at(0) == '[' && line.at(line.length() - 1) == ']') {
        	std::string sectionName = line.substr(1,line.length() - 2);
        	if (sectionName == "version") {
        		section = MF_VERSION;
			} else if (sectionName == "files") {
        		section = MF_FILES;
        	} else {
        		std::cout << "Unknown Manifest section: [" << sectionName << "]" << std::endl;
        		section == MF_UNKNOWN;
        	}
        } else 
        // Interpret a version line
        if (section == MF_VERSION) {
        	std::istringstream linestream(line);
        	std::string field;

        	std::getline(linestream, field, ',');
        	this->fileVersion = std::stoul(field);
        	std::getline(linestream, this->checksum, ',');
        	std::getline(linestream, this->version, ',');
        } else
        // Interpret a line for a file
        if (section == MF_FILES ) {
	        std::istringstream linestream(line);
	        
	        std::string field;
	        ManifestEntry entry;
	        std::getline(linestream, entry.path, ',');
	        std::getline(linestream, field, ',');
	        entry.sizeA = std::stoul(field);
	        std::getline(linestream, entry.checkA, ',');
	        std::getline(linestream, field, ',');
	        entry.sizeB = std::stoul(field);
	        std::getline(linestream, entry.checkB, ',');
	        std::getline(linestream, entry.checkC, ',');
	        this->files.push_back(entry);
    	}
    }
}

ManifestEntry ManifestFile::find(std::string path) {
	ManifestEntry test;
	test.path = path;
	std::vector<ManifestEntry>::iterator it = std::lower_bound(this->files.begin(), this->files.end(), test, manifestCompare);
	if (it->path == test.path) {
		return *it;
	} else {
		return test;
	}
}