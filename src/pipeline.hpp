#pragma once
#include <iostream>
#include <vector>
#include <string>

class InputStage {
protected:
	// The wrapped predecessor to this stage
	InputStage* wrapped = nullptr;
public:
	
	// The function to build up the input stream once it goes live
	virtual std::istream* getStream(std::istream* source) = 0;
	
	// Clean up the Input if necessary
	virtual void cleanup();

	// Delete this stage
	virtual ~InputStage();
};

class InitialInputStage : public InputStage {

public:
	// Return the parameter
	std::istream* getStream(std::istream* source);
};

class DumpInputStage : public InputStage {
	std::string filename;
	std::istream* contained = nullptr;

public:
	// Creates a new dump stage
	DumpInputStage(InputStage* wrapped, std::string filename);

	// Cleaning up
	void cleanup();
	
	// Return the parameter
	std::istream* getStream(std::istream* source);
};

class GenericInputStage : public InputStage {

protected:
	// The function pointer to create this stage stream
	std::istream* (*construct)(std::istream* src);
	std::istream* contained = nullptr;

public:
	// Create the stage
	GenericInputStage(InputStage* wrapped, std::istream* (*construct)(std::istream* src));

	// Cleaning things up
	void cleanup();

	// Calling this construct function
	std::istream* getStream(std::istream* source);
};

class OutputStage {

protected:
	// The wrapped successor to this stage
	OutputStage* wrapped = nullptr;

public:
	// The function to build up the output stream once it goes live
	// The name may be used for logging/saving purposes
	virtual std::ostream* getStream(std::ostream* sink, std::string name) = 0;

	// Clean up the input if necessary
	virtual void cleanup();

	// Deletes this stage
	virtual ~OutputStage();

};

class InitialOutputStage : public OutputStage {

public:
	// Return through wrapped
	std::ostream* getStream(std::ostream* sink, std::string name);
};

class GenericOutputStage : public OutputStage {

protected:
	// The function pointer to create this stage stream
	std::ostream* (*construct)(std::ostream* sink);
	std::ostream* contained = nullptr;

public:
	// Constructor with the predecessor
	GenericOutputStage(OutputStage* wrapped, std::ostream* (*construct)(std::ostream* sink));

	// Cleaning things up
	void cleanup();

	// Calling the construct method
	std::ostream* getStream(std::ostream* sink, std::string name);
};

class ManageStage {

public:
	// The main working function for this managing stage
	virtual void run(InputStage* input, OutputStage* output, std::vector<std::string> files) = 0;
};

class TransformStage {

public:
	// The main function for this transformation
	virtual void run(std::istream* source, std::ostream* sink) = 0;
};

class TransformManageStage : public ManageStage {
protected:
	TransformStage* transform;
public:
	// The transformation in this manage stage
	TransformManageStage(TransformStage* transform);
	void run(InputStage* input, OutputStage* output, std::vector<std::string> files);
};
