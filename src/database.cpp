#include "database.hpp"

#include <fstream>
#include <algorithm>


/*
 * Database read functions
 */

void read(std::istream& stream, int32_t& val)
{
	stream.read((char*) &val, 4);
}

void read(std::istream& stream, uint32_t& val)
{
	stream.read((char*) &val, 4);
}

void read(std::istream& stream, int64_t& val)
{
    int32_t addr, cur;
    read(stream, addr);
    cur = stream.tellg();
    stream.read((char*) &val, 8);
    stream.seekg(cur);
}

void read(std::istream& stream, uint64_t& val)
{
    int32_t addr, cur;
    read(stream, addr);
    cur = stream.tellg();
    stream.read((char*) &val, 8);
    stream.seekg(cur);
}

void read(std::istream& stream, float& val)
{
	stream.read((char*) &val, 4);
}

void read(std::istream& stream, std::string& val)
{
	int32_t addr, cur;
    read(stream, addr);
    cur = stream.tellg();
    stream.seekg(addr);
    std::getline(stream, val, '\0');
    stream.seekg(cur);
}

void read(std::istream& stream, bool& val)
{
	int32_t test;
    read(stream, test);
    val = (test != 0);
}

void read(std::istream& stream, void*& val)
{
	// Do nothing, this is weird!
}

/*
 * Helpers
 */

int32_t readINT32(std::istream& stream)
{
	int32_t val;
	read(stream, val);
	return val;
}

/*
 * Field readers
 */

void readField(std::istream& stream, int32_t& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref = 0;
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, uint32_t& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref = 0;
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, int64_t& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref = 0;
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, uint64_t& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref = 0;
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, float& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref = 0;
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, std::string& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref.clear();
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, bool& ref)
{
	int32_t data_type = readINT32(stream);
	if (data_type == 0)
	{
		ref = false;
	}
	else
	{
		read(stream, ref);
	}
}

void readField(std::istream& stream, void*& val)
{
	// Do nothing, this is weird!
}

/*
 * FDB stuff
 */

int FileDataBase::loadFromFile(std::string filename)
{
	std::ifstream infile(filename);
	if (infile.is_open())
	{
		this->loadFromStream(infile);
		infile.close();
		return 0;
	}
	else
	{
		std::cerr << "Failed to load '" << filename << "' as database!" << std::endl;
		return 1;
	}
}

bool tableComparator(fdb_table_t t1, fdb_table_t t2)
{
	return std::lexicographical_compare(t1.name.begin(), t1.name.end(), t2.name.begin(), t2.name.end());
}

fdb_table_t tableForName(std::string name)
{
	return {0,0,0,0,0,0,0,0,name,std::vector<fdb_column_t>()};
}

std::string fdbReadString(std::istream& stream, int32_t data)
{
	if (data == -1) return "";
	stream.seekg(data, stream.beg);
	std::string value;
	std::getline(stream, value, '\0');
	return value;
}

fdb_table_t FileDataBase::findTableByName(std::string name)
{
	std::vector<fdb_table_t>::iterator it = std::lower_bound(
		this->tables.begin(), this->tables.end(), tableForName(name), tableComparator
	);
	return (it->name == name) ? *it : tableForName("");
}

int FileDataBase::loadFromStream(std::istream& infile)
{
	// Load the basics
	read(infile, this->table_count);
	read(infile, this->table_header_addr);

	// Load all tables
	infile.seekg(this->table_header_addr);
	for (int i = 0; i < table_count; i++)
	{
		// Generate a new entry
		fdb_table_t entry;

		read(infile, entry.column_header_addr);
		read(infile, entry.row_top_header_addr);

		int32_t cur = infile.tellg();
		
		if (entry.column_header_addr != -1)
		{
			infile.seekg(entry.column_header_addr, infile.beg);
			
			read(infile, entry.column_count);
			read(infile, entry.name_addr);
			read(infile, entry.column_data_addr);

			// Read the name
			entry.name = fdbReadString(infile, entry.name_addr);

			infile.seekg(entry.column_data_addr);
			for (int j = 0; j < entry.column_count; j++)
			{
				fdb_column_t column;

				read(infile, column.data_type);
				read(infile, column.col_name_addr);

				int save = infile.tellg();
				column.name = fdbReadString(infile, column.col_name_addr);
				infile.seekg(save);

				entry.columns.push_back(column);
			}
		}
		
		if (entry.row_top_header_addr != -1)
		{
			infile.seekg(entry.row_top_header_addr);
		
			read(infile, entry.row_count);
			read(infile, entry.row_header_addr);
		}

		tables.push_back(entry);

		infile.seekg(cur, infile.beg);
	}

	return 0;
}

/*
 * Calculates the address of the row_header entry for this hash
 */
int32_t get_row_header_entry_addr(const fdb_table_t& table, int32_t index)
{
	int32_t slot = index % table.row_count;
	return table.row_header_addr + (slot * sizeof(int32_t));
}

FDBStatement::FDBStatement(fdb_table_t& table, std::istream& file, int32_t index) : table(table), file(file)
{
	if (this->table.name.empty()) throw 5;

	int32_t row_header_entry_addr = get_row_header_entry_addr(this->table, index);
	this->file.seekg(row_header_entry_addr);

	read(this->file, this->row_info_addr);
}

void FDBStatement::execute(FDBQuery& query)
{
	bool found;
	while (this->seek_next_row_data())
	{	
		if (query.where(file))
		{
			found = true;
			query.select(file);
		}
		else if (found)
		{
			break;
		}
	}
}

bool FDBStatement::seek_next_row_data()
{
	while (this->row_info_addr != -1)
	{
		this->file.seekg(this->row_info_addr);

		int32_t row_data_header_addr;
		read(this->file, row_data_header_addr);
		read(this->file, this->row_info_addr);

		if (row_data_header_addr == -1) continue;
		this->file.seekg(row_data_header_addr);

		int32_t column_count, row_data_addr;
		read(this->file, column_count);
		read(this->file, row_data_addr);

		this->file.seekg(row_data_addr);
		return true;
	}
	return false;
}

int32_t hash(int32_t in, int32_t mod)
{
	return in % mod;
}