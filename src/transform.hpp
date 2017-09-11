#pragma once

#include "pipeline.hpp"


class ConfigTransformStage : public TransformStage {
public:
	void run(std::istream* source, std::ostream* sink);
};

class NoTransformStage : public TransformStage {
public:
	void run(std::istream* source, std::ostream* sink);
};

class ManifestTransformStage : public TransformStage {
	std::string base_url;
public:
	ManifestTransformStage(std::string base_url);
	void run(std::istream* source, std::ostream* sink);
};

class PackIndexTransformStage : public TransformStage {
public:
	void run(std::istream* source, std::ostream* sink);
};

class MD5TransformStage : public TransformStage {
public:
	void run(std::istream* source, std::ostream* sink);
};

class SD0TransformStage : public TransformStage {
public:
	void run(std::istream* source, std::ostream* sink);
};

class ClientExtractorStage : public TransformStage
{
protected:
	// Folder with all sd0 compressed remote files
	std::string folder;

public:
	// Constructor, providing the source folder
	ClientExtractorStage(std::string folder);

	// The running method
	void run(std::istream* source, std::ostream* sink);
};
