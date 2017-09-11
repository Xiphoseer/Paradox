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

struct FDBQuery
{
	std::function<bool(std::istream&)> where;
	std::function<void(std::istream&)> select;
};

struct FDBStatement
{
	fdb_table_t& table;
	std::istream& file;
	int32_t row_info_addr;

	FDBStatement(fdb_table_t& table, std::istream& file, int32_t index);
	void execute(FDBQuery& query);
	bool seek_next_row_data();
};

std::string fdbReadString(std::istream& stream, int32_t data);

template<typename T>
struct TypeSelector
{
	std::vector<T>& list;

	TypeSelector(std::vector<T>& list) : list(list) {};
	void operator()(std::istream& file)
	{
		T entry;
		readDB(entry, file);
		list.push_back(entry);
	}
};

template<typename T>
struct PrimaryKeyPredicate
{
	T ref;

	PrimaryKeyPredicate(T ref) : ref(ref) {};
	bool operator()(std::istream& file)
	{
		T val;
		readField(file, val);
		file.seekg(-8, file.cur);
		return val == ref;
	}
};

int32_t hash(int32_t in, int32_t mod);

template<typename E, typename K>
std::vector<E> makeTypeQuery(fdb_table_t table, std::istream& file, K primary_key)
{
	std::vector<E> list;
	FDBQuery query = {PrimaryKeyPredicate<K>(primary_key), TypeSelector<E>(list)};
	FDBStatement stmt(table, file, hash(primary_key, table.row_count));
	stmt.execute(query);
	return list;
}