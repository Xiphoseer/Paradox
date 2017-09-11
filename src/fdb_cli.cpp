#include "fdb_cli.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>

#include <Magick++.h>

#include "filesystem.hpp"
#include "cli.hpp"
#include "database.hpp"
#include "trim.hpp"
#include "cdclient.hpp"

opt_t fdb_options[] = 
{
	{ "test",			&fdb_test, 			0 },
	{ "convert",		&fdb_convert,	 	0 },
	{ "header",			&fdb_header,	 	0 },
	{ "docs-table",		&fdb_docs_table,	0 },
	{ "docs-tables",	&fdb_docs_tables,	0 },
	{ "all-tables",		&fdb_all_tables,	0 },
	{ 0, 0, 0 }
};

const int lens[] = {4,15,4,15,2048,3,20,4,30};
const char* types[] = {"NOTHING", "INTEGER", "UNKNOWN1", "FLOAT", "TEXT", "BOOLEAN", "BIGINT", "UNKNOWN2", "VARCHAR" };

int main_fdb(int argc, char** argv)
{
	int optind = 1;

	if (argc <= optind) {
		std::cout << "Usage: fdb <subcommand> ..." << std::endl;
		return 1;
	}

	return call("DatabaseCLI", fdb_options, argv[optind], argc - optind, argv + optind);
}

void print_state (const std::ios& stream) {
  std::cout << " good()=" << stream.good();
  std::cout << " eof()=" << stream.eof();
  std::cout << " fail()=" << stream.fail();
  std::cout << " bad()=" << stream.bad();
  std::cout << std::endl;
}

void print(int i)
{
	std::cout << i << std::endl;
}

int fdb_test(int argc, char** argv)
{
	if (argc <= 2)
	{
		std::cout << "Usage: fdb test <database> <pk>" << std::endl;
		return 1;
	}

	FileDataBase fdb;
	std::ifstream file(argv[1]);

	if (fdb.loadFromStream(file) != 0) return 2;

	std::string table_name = "BehaviorParameter";
	fdb_table_t table = fdb.findTableByName(table_name);
	int32_t index = std::atoi(argv[2]);

	// -----------------
	FDBStatement stmt(table, file, index);
	std::vector<BehaviorParameter> list;

	FDBQuery query =
	{
		[index](std::istream& file)
		{
			int32_t pk;
			readField(file, pk);
			file.seekg(-8, file.cur);
			return pk == index;
		},
		[&list](std::istream& file)
		{
			BehaviorParameter param;
			readDB(param, file);
			list.push_back(param);
		}
	};

	bool found;
	while (stmt.seek_next_row_data())
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
	// -----------------


	file.close();

	for (BehaviorParameter param : list)
	{
		std::cout << std::setw(5) << param.m_behaviorID << " ";
		std::cout << std::setw(20) << param.m_parameterID << " ";
		std::cout << param.m_value << std::endl;
	}

	return 0;
}

int fdb_convert(int argc, char** argv)
{
	if (argc <= 2)
	{
		std::cout << "Usage: fdb test <input> <output>" << std::endl;
		return 1;
	}

	Magick::Image img;
	img.read(argv[1]);
	img.write(argv[2]);

	return 0;
}

int fdb_all_tables(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cout << "Usage: fdb test <database>" << std::endl;
		return 1;
	}

	std::string path = "docs/tables/all.rst";
	ensure_dir_exists(path);
	std::ofstream ofile(path);

	ofile << "Table Overview" << std::endl;
	ofile << "==============" << std::endl;
	ofile << std::left << std::endl;

	FileDataBase fdb;
	if (fdb.loadFromFile(argv[1]) != 0) return 2;

	int colwidth = 50;
	int typewidth = 10;

	for (int i = 0; i < fdb.tables.size(); i++)
	{
		fdb_table_t& table = fdb.tables.at(i);
		ofile << table.name << std::endl;
		ofile << std::string(table.name.size(), '-') << std::endl;
		ofile << std::endl;

		ofile << std::string(colwidth, '=') << "  " << std::string(typewidth, '=') << std::endl;
		ofile << std::setw(colwidth) << "Column" << "  " << std::setw(typewidth) << "Type" << std::endl;
		ofile << std::string(colwidth, '=') << "  " << std::string(typewidth, '=') << std::endl;

		for (int j = 0; j < table.columns.size(); j++)
		{
			fdb_column_t& column = table.columns.at(j);
			ofile << std::setw(colwidth) << column.name << "  " << std::setw(typewidth) << types[column.data_type] << std::endl;
		}

		ofile << std::string(colwidth, '=') << "  " << std::string(typewidth, '=') << std::endl;
		ofile << std::endl;

		ofile << table.row_count << " Slots" << std::endl;
		ofile << std::endl;
	}

	ofile.close();

}

const char* ctypes[] = {"void*", "int32_t", "err_t", "float", "std::string", "bool", "int64_t", "err2_t", "std::string" };

int fdb_header(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cout << "Usage: fdb test <database>" << std::endl;
		return 1;
	}

	std::string path = "code/cdclient.hpp";
	std::string path2 = "code/cdclient.cpp";
	ensure_dir_exists(path);
	ensure_dir_exists(path2);
	std::ofstream ofile(path);
	std::ofstream ifile(path2);

	ofile << "#pragma once" << std::endl;
	ofile << std::left << std::endl;
	ofile << "#include <string>" << std::endl;
	ofile << "#include <iostream>" << std::endl;
	ofile << std::endl;
	ofile << "#include \"database.hpp\"" << std::endl;
	ofile << std::endl;

	ifile << "#include \"cdclient.hpp\"" << std::endl;
	ifile << std::endl;
	ofile << std::endl;

	FileDataBase fdb;
	if (fdb.loadFromFile(argv[1]) != 0) return 2;

	int typewidth = 15;

	for (int i = 0; i < fdb.tables.size(); i++)
	{
		fdb_table_t& table = fdb.tables.at(i);
		
		ofile << "// SlotCount: " << table.row_count << std::endl;
		ofile << "typedef struct" << std::endl;
		ofile << "{" << std::endl;

		ifile << "void readDB(" << table.name << "& entry, std::istream& file)" << std::endl;
		ifile << "{" << std::endl;

		for (int j = 0; j < table.columns.size(); j++)
		{
			fdb_column_t& column = table.columns.at(j);
			ofile << "    " << std::setw(typewidth) << ctypes[column.data_type] << " m_" << column.name << ";" << std::endl;
			ifile << "    readField(file, entry.m_" << column.name << ");" << std::endl;
		}

		ofile << "}" << std::endl;
		ofile << table.name << ";" << std::endl;
		ofile << std::endl;
		ofile << "void readDB(" << table.name << "& entry, std::istream& file);" << std::endl;
		ofile << std::endl;

		ifile << "}" << std::endl;
		ifile << std::endl;
	}

	ofile.close();
	ifile.close();
}

int max(int a, int b)
{
	return (a < b) ? b : a;
}

void read_row(std::istream& file, std::ostream& ofile, int32_t row_data_addr, int* args, int* widths, int count)
{	
	file.seekg(row_data_addr);
	for (int k = 0; k < count; k++)
	{
		file.seekg(row_data_addr + 8 * args[k]);
		int32_t data_type;
		read(file, data_type);

		int len = widths[k];
		
		const char* before = (k > 0) ? "  " : "";

		switch (data_type)
		{
			case 1: // INT
			case 5: // BOOL
				int32_t int_val;
				read(file, int_val);
				ofile << before << std::setw(len) << int_val;
				break;
			case 3: // FLOAT
				float float_val;
				read(file, float_val);
				ofile << before << std::setw(len) << float_val;
				break;	
			case 4: // TEXT
			case 8: // VARCHAR
			{
				int32_t string_addr;
				read(file, string_addr);
				std::string str = fdbReadString(file, string_addr);
				trim(str);
				std::string str_val = str.empty() ? "" : "``" + str + "``";
				ofile << before << std::setw(len) << str_val;
			}
			break;
			case 6: //BIGINT
				int32_t int_addr;
				read(file, int_addr);
				file.seekg(int_addr);
				int64_t bigint_val;
				read(file, bigint_val);
				ofile << before << std::setw(len) << bigint_val;
				break;
			default:
				int32_t val;
				read(file, val);
				ofile << before << std::setw(len) << val;
		}
	}

	ofile << std::endl;
}

int read_row_infos(std::istream& file, std::ostream& ofile, int32_t row_info_addr, int* args, int* widths, int count)
{
	int32_t row_data_header_addr, column_count, row_data_addr;

	while (row_info_addr != -1)
	{
		file.seekg(row_info_addr);

		read(file, row_data_header_addr);
		read(file, row_info_addr);

		if (row_data_header_addr == -1) continue;

		file.seekg(row_data_header_addr);
		read(file, column_count);
		read(file, row_data_addr);
		
		if (row_data_addr == -1) continue;

		/*std::cout << std::setw(6) << r << " ";*/

		read_row(file, ofile, row_data_addr, args, widths, count);
	}
}

int fdb_docs_table(int argc, char** argv)
{
	if (argc <= 3)
	{
		std::cout << "Usage: fdb docs-table <database> <table> <col_1> [<col_2> ... <col_n>]" << std::endl;
		return 1;
	}

	FileDataBase fdb;
	if (fdb.loadFromFile(argv[1]) != 0) return 2;

	std::string table_name = argv[2];
	fdb_table_t table = fdb.findTableByName(table_name);

	if (table.name.empty()) return 5;

	std::stringstream base_path("");
	base_path << "docs/tables/" << table_name << ".rst";
	ensure_dir_exists(base_path.str());
	std::ofstream ofile(base_path.str());
	ofile << std::left;

	ofile << table_name << std::endl;
	ofile << std::string(table_name.size(), '=') << std::endl;
	ofile << std::endl;

	std::vector<std::string> columns;
	for (int i = 3; i < argc; i++)
	{
		columns.push_back(argv[i]);
	}

	std::stringstream underline("");
	std::stringstream header("");
	header /*<< "ID     "*/ << std::left;
	/*underline << "====== ";*/

	int i = 0;
	int args[columns.size()];
	int widths[columns.size()];
	for (int j = 0; j < table.columns.size(); j++)
	{
		fdb_column_t& column = table.columns.at(j);
		if (std::find(columns.begin(), columns.end(), column.name) != columns.end())
		{
			int len = max(lens[column.data_type], column.name.size());
			header << ((i > 0) ? "  " : "") << std::setw(len) << column.name;
			underline << ((i > 0) ? "  " : "") << std::string(len, '=');
			widths[i] = len;
			args[i++] = j;
		}
	}

	ofile << underline.str() << std::endl;
	ofile << header.str() << std::endl;
	ofile << underline.str() << std::endl;

	std::ifstream file(argv[1]);
	if (!file.is_open()) return 4;

	int cur = table.row_header_addr;
	for (int r = 0; r < table.row_count; r++)
	{
		file.seekg(cur);
		int32_t row_info_addr;
		
		read(file, row_info_addr);
		cur = file.tellg();
		
		read_row_infos(file, ofile, row_info_addr, args, widths, i);
	}

	ofile << underline.str() << std::endl;
	ofile << std::endl;

	file.close();
	ofile.close();

	return 0;
}

int fdb_docs_tables(int argc, char** argv)
{
	if (argc <= 3)
	{
		std::cout << "Usage: fdb docs-tables <database> <table> <col_1> [<col_2> ... <col_n>]" << std::endl;
		return 1;
	}

	FileDataBase fdb;
	if (fdb.loadFromFile(argv[1]) != 0) return 2;

	std::string table_name = argv[2];
	fdb_table_t table = fdb.findTableByName(table_name);

	if (table.name.empty()) return 5;

	std::stringstream base_path("");
	base_path << "docs/tables/" << table_name << ".rst";
	ensure_dir_exists(base_path.str());
	std::ofstream index_file(base_path.str());

	std::cout << base_path.str() << std::endl;
	index_file << table_name << std::endl;
	index_file << std::string(table_name.size(), '=') << std::endl;
	index_file << std::endl;
	index_file << "Rows:" << table.row_count << std::endl << std::endl;
	index_file << std::endl;
	index_file << ".. toctree::" << std::endl;
	index_file << "\t:maxdepth: 1" << std::endl;
	index_file << "\t:caption: Contents:" << std::endl;
	index_file << std::endl;

	std::vector<std::string> columns;
	for (int i = 3; i < argc; i++)
	{
		columns.push_back(argv[i]);
	}

	std::stringstream underline("");
	std::stringstream header("");
	header /*<< "ID     "*/ << std::left;
	/*underline << "====== ";*/

	int i = 0;
	int args[columns.size()];
	int widths[columns.size()];
	for (int j = 0; j < table.columns.size(); j++)
	{
		fdb_column_t& column = table.columns.at(j);
		if (std::find(columns.begin(), columns.end(), column.name) != columns.end())
		{
			int len = max(lens[column.data_type], column.name.size());
			header << ((i > 0) ? "  " : "") << std::setw(len) << column.name;
			underline << ((i > 0) ? "  " : "") << std::string(len, '=');
			widths[i] = len;
			args[i++] = j;
		}
	}

	std::ofstream ofile;
	int fileid = -1;

	std::ifstream file(argv[1]);
	if (!file.is_open()) return 4;

	int cur = table.row_header_addr;
	for (int r = 0; r < table.row_count; r++)
	{
		file.seekg(cur);
		int32_t row_info_addr, row_data_header_addr, column_count, row_data_addr;
		
		read(file, row_info_addr);
		cur = file.tellg();
		
		bool started = (row_info_addr != -1);
		if (started)
		{
			int entries_per_page = 500;

			int newfid = r / entries_per_page;
			if (newfid != fileid)
			{
				if (ofile.is_open()) ofile.close();

				fileid = newfid;
				std::stringstream path("");
				path << "docs/tables/" << table.name << "/" << fileid << ".rst";
				std::string path_str = path.str();
				ensure_dir_exists(path_str);
				std::cout << path_str << std::endl;
				ofile.open(path_str);
				if (!ofile.is_open()) return 7;

				index_file << "\t" << table.name << "/" << fileid << std::endl;

				std::stringstream title("");
				title << (fileid * entries_per_page) << " to " << ((fileid + 1) * entries_per_page - 1);
				std::string title_str = title.str();
				ofile << std::left;
				ofile << title_str << std::endl;
				ofile << std::string(title_str.size(), '=') << std::endl;
				ofile << std::endl;
			}
			
			ofile << table.name << " #" << r << std::endl;
			ofile << std::string(table.name.size() + log10(r) + 3, '-') << std::endl;
			ofile << std::endl;
			ofile << underline.str() << std::endl;
			ofile << header.str() << std::endl;
			ofile << underline.str() << std::endl;

			read_row_infos(file, ofile, row_info_addr, args, widths, i);

			ofile << underline.str() << std::endl;
			ofile << std::endl;	
		}
	}

	if (ofile.is_open()) ofile.close();

	index_file << std::endl;
	index_file.close();
	return 0;
}