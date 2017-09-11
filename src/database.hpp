#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include <stdint.h>


void read(std::istream& stream, int32_t& val);
void read(std::istream& stream, uint32_t& val);
void read(std::istream& stream, int64_t& val);
void read(std::istream& stream, uint32_t& val);
void read(std::istream& stream, float& val);
void read(std::istream& stream, std::string& val);
void read(std::istream& stream, bool& val);
void read(std::istream& stream, void*& val);

void readField(std::istream& stream, int32_t& val);
void readField(std::istream& stream, uint32_t& val);
void readField(std::istream& stream, int64_t& val);
void readField(std::istream& stream, uint64_t& val);
void readField(std::istream& stream, float& val);
void readField(std::istream& stream, std::string& val);
void readField(std::istream& stream, bool& val);
void readField(std::istream& stream, void*& val);


typedef struct
{
	int32_t data_type;
	int32_t col_name_addr;
	std::string name;
}
fdb_column_t;

typedef struct
{
	int32_t column_header_addr;
	int32_t some_data;
	int32_t column_count;
	int32_t name_addr;
	int32_t column_data_addr;
	int32_t row_top_header_addr;
	int32_t row_count;
	int32_t row_header_addr;
	std::string name;
	std::vector<fdb_column_t> columns;
}
fdb_table_t;

struct FileDataBase
{
	int32_t table_count;
	int32_t table_header_addr;
	std::vector<fdb_table_t> tables;

	int loadFromFile(std::string filename);
	int loadFromStream(std::istream& input);

	fdb_table_t findTableByName(std::string name);
};

struct FDBStatement
{
	fdb_table_t& table;
	std::istream& file;
	int32_t row_info_addr;

	FDBStatement(fdb_table_t& table, std::istream& file, int32_t index);
	bool seek_next_row_data();
};

struct FDBQuery
{
	std::function<bool(std::istream&)> where;
	std::function<void(std::istream&)> select;
};

std::string fdbReadString(std::istream& stream, int32_t data);