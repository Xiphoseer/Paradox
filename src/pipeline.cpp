#include "pipeline.hpp"

#include <fstream>
#include "stream.hpp"

extern int verbose_flag;

void InputStage::cleanup() {
	if (wrapped != nullptr) wrapped->cleanup();
}

InputStage::~InputStage() {
	if (wrapped != nullptr) delete wrapped;
}

std::istream* InitialInputStage::getStream(std::istream* source) {
	return source;
}

DumpInputStage::DumpInputStage(InputStage* wrapped, std::string filename) : filename(filename)
{
	this->wrapped = wrapped;
}

std::istream* DumpInputStage::getStream(std::istream* source) {
	std::cerr << "1" << std::endl;
	std::istream* in = wrapped->getStream(source);
	std::cerr << "2" << std::endl;
	std::streambuf *buf = new dump_istreambuf<1024>(in, filename);
	std::cerr << "3" << std::endl;
	contained = new closebuf_istream(buf);
	std::cerr << "4" << std::endl;
	return contained;
}

void DumpInputStage::cleanup() {
	if (wrapped != nullptr) wrapped -> cleanup();
	if (contained != nullptr) {
		delete contained;
		contained = nullptr;
	}
}

std::istream* GenericInputStage::getStream(std::istream* source) {
	return contained = construct(wrapped->getStream(source));
}

GenericInputStage::GenericInputStage(InputStage* wrapped, std::istream* (*construct)(std::istream* src)) : construct(construct) {
	this->wrapped = wrapped;
}

void GenericInputStage::cleanup() {
	if (wrapped != nullptr) wrapped -> cleanup();
	if (contained != nullptr) {
		delete contained;
		contained = nullptr;
	}
}

void OutputStage::cleanup() {
	if (wrapped != nullptr) wrapped -> cleanup();
}

OutputStage::~OutputStage() {
	if (wrapped != nullptr) delete wrapped;	
}

std::ostream* InitialOutputStage::getStream(std::ostream* source, std::string name) {
	return source;
}

std::ostream* GenericOutputStage::getStream(std::ostream* source, std::string name) {
	return wrapped->getStream(construct(source), name);
}

GenericOutputStage::GenericOutputStage(OutputStage* wrapped, std::ostream* (*construct)(std::ostream* sink)) : construct(construct) {
	this->wrapped = wrapped;
}

void GenericOutputStage::cleanup() {
	if (wrapped != nullptr) wrapped -> cleanup();
	if (contained != nullptr) {
		delete contained;
		contained = nullptr;
	}
}

TransformManageStage::TransformManageStage(TransformStage* transform) : transform(transform) {}

void TransformManageStage::run(InputStage* input, OutputStage* output, std::vector<std::string> files)
{
	bool from_stdin = files.empty();
	bool first = true;

	if (from_stdin) {
		std::istream* in = input->getStream(&std::cin);
		std::ostream* out = output->getStream(&std::cout, "stdin");
		transform->run(in, out);
		input->cleanup();
		output->cleanup();
	}

	for (std::string& file : files) {
		
		std::ifstream infile(file, std::ios::binary);
		std::istream* in = input->getStream(&infile);
		std::ostream* out = output->getStream(&std::cout, file);
		transform->run(in, out);
		out->flush();
		infile.close();
		input->cleanup();
		output->cleanup();

		if (!first) {
			first = false;
			if (verbose_flag) std::cout << "---------------------------------------------------------------------";
		}
	}
}