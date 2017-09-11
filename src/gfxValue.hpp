#pragma once

#include <string>
#include <memory>

namespace std {
	std::string to_string(std::string val) {
		return val;
	}

	std::string to_string(void* val) {
		return "[NULL]";
	}
}

/*
 * Enum for all possible types of grapics values
 *
 */
enum gfxValueType {
	gfxUnknownType = -1,
	gfxStringType = 0,
	gfxShortType = 1,
	gfxUnsignedLongType = 5,
	gfxSignedLongType = 6,
	gfxBooleanType = 7,
};

gfxValueType gfxType(char in) {
	return ((0 <= in && in <= 1) || (5 <= in && in <= 7) ) ? (gfxValueType) in : gfxUnknownType;
}

template<typename T>
gfxValueType getGfxType() { return gfxUnknownType; }

template<>
gfxValueType getGfxType<std::string>() { return gfxStringType; }

template<>
gfxValueType getGfxType<short>() { return gfxShortType; }

template<>
gfxValueType getGfxType<unsigned long>() { return gfxUnsignedLongType; }

template<>
gfxValueType getGfxType<bool>() { return gfxBooleanType; }

/*
 * The base class for all concrete graphics value
 * implementations.
 * 
 */
class gfxValue {
public:
	virtual std::string toString() = 0;
	virtual gfxValueType getType() = 0;
	virtual std::unique_ptr<gfxValue> copy() = 0;
};

/*
 * A graphics value implementation
 *
 */
template<typename T>
class gfxBasicValue : public gfxValue {

	// The contained data
	T data;
public:

	// Transforms the value to it's string representation
	std::string toString() { return std::to_string(data); }
	
	// Gets the type of this value
	gfxValueType getType() { return getGfxType<T>(); }
	
	// Constructor
	gfxBasicValue(T val) : data(val) {}

	// Gets the contained value
	T getData() { return data; }
	
	// Copies the data
	std::unique_ptr<gfxBasicValue<T>> copyT() { return std::make_unique<gfxBasicValue<T>>(data); }
	std::unique_ptr<gfxValue> copy() { return copyT(); }
};

/*
 * A simple reference class wrapper that makes the value copy-constructable
 */
class gfxReference {
	std::unique_ptr<gfxValue> ptr;
public:
	gfxReference(gfxValue* ptr) : ptr(std::unique_ptr<gfxValue>(ptr)){}
	gfxReference(const gfxReference& other) : ptr(other->copy()) {}
	gfxValue* operator->() const { return ptr.get(); }
	operator bool() const { return ptr.get() != nullptr; }
};

// Standard type definitions
typedef gfxBasicValue<std::string> gfxString;
typedef gfxBasicValue<short> gfxShort;
typedef gfxBasicValue<unsigned long> gfxUnsignedLong;
typedef gfxBasicValue<bool> gfxBoolean;

// Function to create a gfxValue value from a string
gfxReference toGfxValue(gfxValueType type, std::string value) {

	switch(type) {
		case gfxStringType:
			return gfxReference(new gfxString(value));
		case gfxShortType:
			return gfxReference(new gfxShort(std::stoi(value)));
		case gfxUnsignedLongType:
			return gfxReference(new gfxUnsignedLong(std::stoul(value)));
		case gfxBooleanType:
			return gfxReference(new gfxBoolean(value == "1"));
		default:
			return gfxReference(new gfxBasicValue<void*>(nullptr));
	}
}