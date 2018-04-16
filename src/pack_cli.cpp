#include "pack_cli.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <unistd.h>

#include <assembly/catalog.hpp>
#include <assembly/package.hpp>
#include <assembly/manifest.hpp>
#include <assembly/filesystem.hpp>
#include <assembly/cli.hpp>

#include "pack.hpp"

#include "sd0_stream.hpp"


using namespace assembly::package;
using namespace assembly::manifest;
using namespace assembly::catalog;


cli::opt_t pack_options[] =
{
	{ "crc",			&pack_crc, 			"Compute CRC-23 has for a filename"					},
	{ "pack-index",		&pack_pack_index,	"Get the pack file assiciated with a CRC"			},
	{ "file-info",		&pack_file_info,	"Check if file exists and get checksum and size"	},
	{ "move-to",		&pack_move_to,		"Move a file into a pack file"						},
	{ "read-catalog",	&pack_read_catalog,	"Load a pack catalog (*.pki)"						},
	{ "name",			&pack_name,			"Get the path of a pack file within the client"		},

	{ "list",			&pack_list,		 	"List all files with CRC in a pack file"			},
	{ "tree",			&pack_tree,		 	"Show the binary tree within the pack file"			},
	{ "all",			&pack_all,		 	"Show all files with CRC in the catalog"			},
	{ "missing",		&pack_missing,	 	"Show files with CRC in manifest not in the catalog"},
	{ "target",			&pack_target,	 	"Show all files supposed to be in a pack"			},
	{ "full-extract",	&pack_full_extract,	"Extract a client"									},

	{ "console",		&console_pack,	 	"Provide an interactive interface"					},
	{ "cli",			&console_pack,		0													},
	{ "help",			&help_pack,			"Show this help message"							},
	{ "test",			&test_pack,		 	0													},
	{ 0, 0, 0 }
};

int main_pack (int argc, char** argv)
{
	char const * catalog = 0;

	char opt = 0;
	optind = 1;
	while ((opt = getopt(argc, argv, "c:")) != -1)
	{
		switch (opt)
		{
			case 'c':
			catalog = optarg;
			break;
		}
	}

	if (argc <= optind) {
		std::cout << "Usage: pack [-c <catalog>] <subcommand> ..." << std::endl;
		return 1;
	}

	/*
	 * When there is no catalog path set and we are not launching cli, set a catalog
	 * TODO: remove at some point?
	 */
	if (catalog == 0 && strcmp(argv[optind], "cli") != 0
					 && strcmp(argv[optind], "console") != 0
					 && strcmp(argv[optind], "missing") != 0
					 && strcmp(argv[optind], "all") != 0)
	{
		catalog = "./versions/primary.pki";
	}

	if (catalog != 0)
	{
		pack::ReadPackCatalog(catalog);
	}

	return cli::call("PackCLI", pack_options, argv[optind], argc - optind, argv + optind);
}

int test_pack (int argc, char** argv)
{
	return 0;
}

int help_pack (int argc, char** argv)
{
	cli::help("PackCLI", pack_options, "Pack.dll command line");
}

int console_pack (int argc, char** argv)
{
	std::string command;
	std::cout << "+-----------------------------+" << std::endl;
	std::cout << "| PackCLI interactive console |" << std::endl;
	std::cout << "+-----------------------------+" << std::endl;
	while (command != "exit")
	{
		std::cout << ">>> ";
		std::getline(std::cin, command);

		if (command == "exit") break;

		int _argc = std::count(command.begin(), command.end(), ' ') + 1;

		char buffer[command.size() + 1];
		strcpy(buffer, command.c_str());

		char* _argv[_argc];
		//_argv[0] = (char*) CLI_PATH;
		_argv[0] = (char*) buffer;
		for (int i = 1; i < _argc; i++)
		{
			_argv[i] = std::find(_argv[i-1], buffer + command.size() + 1, ' ') + 1;
			*(_argv[i] - 1) = 0;
		}

		int i = call("PackCLI", pack_options, _argv[0], _argc, _argv) & 0xFF;
		/*if (i != 0) { std::cout << i << " " ; } */
	}

	return 0;
}

int pack_crc(int argc, char** argv)
{
	if (argc > 1)
	{
		uint32_t crc = pack::GetCRCForFilename(argv[1]);
		std::cout << std::hex << crc << std::dec << " (" << crc << ")" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Usage: pack crc <filename>" << std::endl;
		return 1;
	}
}

int pack_pack_index(int argc, char** argv)
{
	if (argc > 1)
	{
		uint32_t crc = std::stoul(argv[1]);
		int packId = pack::GetPackIndex(crc);
		std::cout << "Pack Index: " << packId << std::endl;
		return 0;
	}
	else
	{
		std::cerr << "Usage: pack pack-index <filename-crc>" << std::endl;
		return 1;
	}
}

int pack_file_info(int argc, char** argv)
{
	if (argc > 2)
	{
		uint32_t crc = std::stoul(argv[1]);
		int32_t packIndex = std::stol(argv[2]);
		int32_t bExists, iUncompressedSize;
		char uncompressedChecksum[36];

		pack::GetInfoForFile(crc, packIndex, &bExists, &iUncompressedSize, (char*) uncompressedChecksum);

		if (bExists == 0)
		{
			std::cout << "File does not exist" << std::endl;
		}
		else
		{
			std::cout << std::setw(25) << "Size Uncompressed: " << iUncompressedSize << std::endl;
			std::cout << std::setw(25) << "Checksum Uncompressed: " << std::string(uncompressedChecksum, 32) << std::endl;
		}
		return 0;
	}
	else
	{
		std::cerr << "Usage: pack file-info <filename-crc> <pack-index>" << std::endl;
		return 1;
	}
}

int pack_move_to (int argc, char** argv)
{
	if (argc > 2)
	{
		return pack::MoveFileToPack(argv[1], argv[2], 0, 0, 0, 0, 0);
	}
	std::cout << "Usage: pack move-to <file> <manifestname>" << std::endl;
}

int pack_name (int argc, char** argv)
{
	if (argc > 1)
	{
		int32_t index;
		try
		{
			index = std::stol(argv[1]);
		}
		catch (std::invalid_argument& ia)
		{
			std::cerr << "'" << argv[1] << "' is not an integer" << std::endl;
			return 2;
		}

		char buffer[256];
		if (pack::GetPackName(index, buffer, 256) == 0)
		{
			std::cout << buffer << std::endl;
		}
		else
		{
			std::cerr << "Could not find pack with index " << index << std::endl;
			return 1;
		}
		return 0;
	}
	std::cout << "Usage: pack name <pack-index>" << std::endl;
	return 3;
}

int pack_read_catalog(int argc, char** argv)
{
	bool list = false;

	char opt = 0;
	optind = 1;
	while ((opt = getopt(argc, argv, "l")) != -1)
	{
		switch (opt)
		{
			case 'l':
			list = true;
			break;
		}
	}

	if (argc > optind)
	{
		int32_t count = pack::ReadPackCatalog(argv[optind]);
		std::cout << "# Files: " << count << std::endl;

		if (list)
		{
			char buffer[256];
			for (int32_t i = 0; i < count; i++)
			{
				pack::GetPackName(i, buffer, 256);
				std::cout << std::setw(log10(count) + 1) << i << ": " << buffer << std::endl;
			}
		}
	}
	else
	{
		std::cerr << "Usage: pack read-catalog [-l] <path>" << std::endl;
	}

}

typedef struct Map
{
	uint32_t crc;
	std::string path;
	bool isCompressed;
} map_t;


bool sort(map_t a, map_t b)
{
	return a.path < b.path;
}

int pack_list (int argc, char** argv)
{
	if (argc > 2)
	{
		package_info pack;
		read_from_file(argv[1], pack);

		manifest_file manifest;
        read_from_file(argv[2], manifest);

		std::vector<map_t> files;

		for (std::vector<package_info_entry>::iterator it = pack.files.begin(); it != pack.files.end(); it++)
		{
			files.push_back({it->crc, "???", (it->bCompressed & 0xFF) != 0});
		}

		for (std::vector<manifest_entry>::iterator it = manifest.files.begin(); it != manifest.files.end(); it++)
		{
			uint32_t crc = pack::GetCRCForFilename(it->path.c_str());
			for (std::vector<map_t>::iterator in = files.begin(); in != files.end(); in++)
			{
				if (in->crc == crc)
				{
					in->path = it->path;
					break;
				}
			}
		}

		std::sort(files.begin(), files.end(), sort);
		for (std::vector<map_t>::iterator in = files.begin(); in != files.end(); in++)
		{
			std::cout << std::hex << std::setw(8) << std::setfill('0') << in->crc << ": " << in->path << std::endl;
		}

		return 0;
	}
	else
	{
		std::cout << "Usage: pack list <packfile> <manifest>" << std::endl;
		return 0;
	}
}

void print(package_ptr ptr, int level, std::string prefix, bool top)
{
	if (ptr.valid())
	{
		package_ptr l = ptr.left();
		package_ptr r = ptr.right();
		print(l, level + 1, prefix + "  ", true);
		prefix.replace(level * 2, 2, top ? "\xe2\x94\x8c\xe2\x94\x80" : "\xe2\x94\x94\xe2\x94\x80");
		std::cout << prefix +
			(l.valid() ? (r.valid() ? "\xE2\x94\xBC" : "\xE2\x94\xB4" ) : (r.valid() ? "\xE2\x94\xAC" : "\xe2\x94\x80"))
		+ "\xe2\x94\x84 " << ptr.crc() << std::endl;
		// prefix.replace(level, 1, " ");
		prefix.replace(level * 2, 6, top ? "| " : "  ");
		print(r, level + 1, prefix + "| ", false);
	}
}

int pack_tree(int argc, char** argv)
{
	if (argc > 1)
	{
		package_info info;
		read_from_file(argv[1], info);
		print(package_ptr(&info), 0, "", false);
		return 0;
	}
	std::cout << "Usage: pack tree <packfile>" << std::endl;
	return 1;
}

int32_t find_crc_index(catalog_file& file, uint32_t crc)
{
	int size = file.files.size();
	int index =  (size > 0) ? size / 2 : -1;

	while (index != -1 && file.files.at(index).crc != crc)
	{
		index = file.files.at(index).crc > crc ? file.files.at(index).left : file.files.at(index).right;
	}

	return index;
}

int pack_all(int argc, char** argv)
{
	if (argc > 2)
	{
		manifest_file manifest;
		if (read_from_file(argv[1],manifest) != 0) return 1;

		catalog_file catalog;
		if (read_from_file(argv[2],catalog) != 0) return 2;

		std::vector<std::string> names;
		int count = catalog.files.size();
		names.reserve(count);

		for (int i = 0; i < count; i++){
			names.push_back("???");
		}

		for (int i = 0; i < manifest.files.size(); i++)
		{
			std::string filename = manifest.files.at(i).path;
			uint32_t crc = pack::GetCRCForFilename(filename.c_str());

			int index = find_crc_index(catalog, crc);
			if (index != -1)
			{
				names.at(index) = filename;
			}
		}

		for (int i = 0; i < count; i++)
		{
			std::cout << std::setw(10) << catalog.files.at(i).crc << ": " << names.at(i) << std::endl;
		}
		return 0;
	}

	std::cerr << "Usage: pack tree <manifest> <catalog>" << std::endl;
	return 1;
}

int pack_missing(int argc, char** argv)
{
	if (argc > 2)
	{
		manifest_file manifest;
		if (read_from_file(argv[1],manifest) != 0) return 1;

		catalog_file catalog;
		if (read_from_file(argv[2],catalog) != 0) return 2;

		std::vector<std::string> names;

		for (int i = 0; i < manifest.files.size(); i++)
		{
			std::string filename = manifest.files.at(i).path;
			uint32_t crc = pack::GetCRCForFilename(filename.c_str());

			int index = find_crc_index(catalog, crc);
			if (index == -1 && !fs::exists("./" + filename))
			{
				std::cout << std::setw(10) << crc << ": " << filename << std::endl;
			}
		}
		return 0;
	}

	std::cerr << "Usage: pack tree <manifest> <catalog>" << std::endl;
	return 1;
}

int find_crc_idx(std::vector<uint32_t>& list, int min, int max, uint32_t crc)
{
	if (max < min) return -1;
	int index = (max + min) / 2;

	uint32_t fcrc = list.at(index);

	if (fcrc == crc) return index;
	if (fcrc > crc) return find_crc_idx(list, min, index -1, crc);
	return find_crc_idx(list, index + 1, max, crc);
}

int pack_target(int argc, char** argv)
{
	if (argc > 3)
	{
		manifest_file manifest;
		if (read_from_file(argv[1],manifest) != 0) return 1;

		catalog_file catalog;
		if (read_from_file(argv[2],catalog) != 0) return 2;

		int32_t index = catalog.get_pack_index(argv[3]);

		std::cout << "Index: " << index << std::endl;

		std::vector<uint32_t> crcs;
		std::vector<std::string> strings;

		for (int i = 0; i < catalog.files.size(); i++)
		{
			catalog_entry e = catalog.files.at(i);
			if (e.pack == index)
			{
				crcs.push_back(e.crc);
				strings.push_back("???");
			}
		}

		for (int i = 0; i < manifest.files.size(); i++)
		{
			std::string filename = manifest.files.at(i).path;
			uint32_t crc = pack::GetCRCForFilename(filename.c_str());
			int idx = find_crc_idx(crcs, 0, strings.size() - 1, crc);
			if (idx != -1)
			{
				strings.at(idx) = filename;
			}
		}

		for (int i = 0; i < crcs.size(); i++)
		{
			std::cout << std::setw(10) << crcs.at(i) << ": " << strings.at(i) << std::endl;
		}

		return 0;
	}

	std::cerr << "Usage: pack target <manifest> <catalog> <packpath>" << std::endl;
}

void write_over(std::istream& in, std::ostream& out, int size)
{
	char buffer[1024];

	while (size >= 1024)
	{
		in.read((char*) buffer, 1024);
		out.write((char*) buffer, 1024);
		size -= 1024;
	}

	if (size > 0)
	{
		in.read((char*) buffer, size);
		out.write((char*) buffer, size);
	}
}

int pack_full_extract(int argc, char** argv)
{
	if (argc > 2)
	{
		std::string base_dir = "./";

		if (argc > 3)
		{
			base_dir = std::string(argv[3]);
		}

		std::string out_dir = (argc > 4) ? std::string(argv[4]) : base_dir;

		manifest_file manifest;
		if (read_from_file(argv[1],manifest) != 0) return 1;

		catalog_file catalog;
		if (read_from_file(argv[2],catalog) != 0) return 2;

		int packCount = catalog.pack_files.size();

		std::vector<package_info> packFiles;
		packFiles.reserve(packCount);

		for (int i = 0; i < packCount; i++)
		{
			 packFiles.push_back(package_info());
			 std::string path = catalog.pack_files.at(i);
			 std::replace(path.begin(), path.end(), '\\', '/');

			 read_from_file(base_dir + path, packFiles.at(i));
			 std::cout << packFiles.at(i).files.size() << std::endl;
		}

		for (int i = 0; i < manifest.files.size(); i++)
		{
			std::string path = manifest.files.at(i).path;
			std::cout << "Extracting: " << path << std::endl;
			uint32_t crc = pack::GetCRCForFilename(path.c_str());

			catalog_ptr ptr = find_by_crc(&catalog, crc);
			if (!ptr.valid()) continue;

			int id = ptr.pack_id();

			package_ptr itr = find_by_crc(&(packFiles.at(id)), crc);
			if (!itr.valid()) continue;

			std::replace(path.begin(), path.end(), '\\', '/');
			std::string out = out_dir + path;
			fs::ensure_dir_exists(out);

			std::ofstream ofile(out);

			if (ofile.is_open())
			{
				std::string pth = catalog.pack_files.at(ptr.pack_id());
				std::replace(pth.begin(),pth.end(), '\\', '/');
				std::ifstream ifile(base_dir + pth);

				if (ifile.is_open())
				{
					ifile.seekg(itr.dataAddress());

					if (itr.compressed())
					{
						sd0_istreambuf<1024> ibuf(&ifile);
						std::istream istrm(&ibuf);
						write_over(istrm, ofile, itr.compressedSize());
					}
					else
					{
						int size = itr.uncompressedSize();
						write_over(ifile, ofile, itr.uncompressedSize());
					}

					ifile.close();
				}

				ofile.close();
			}
		}

		return 0;
	}

	std::cerr << "Usage: pack full-extract <manifest> <catalog> [<base-dir>]" << std::endl;
	return 1;
}

int main_catalog (int argc, char** argv)
{
	if (argc > 2)
	{
		catalog_file catalog;
		read_from_file(argv[1],catalog);
		catalog_ptr ptr = find_by_crc(&catalog, pack::GetCRCForFilename(argv[2]));
		if (ptr.valid())
		{
			std::cout << std::setw(20) << "Filename: " << argv[2] << std::endl;
			std::cout << std::setw(20) << "CRC: " << ptr.crc() << std::endl;
			std::cout << std::setw(20) << "Pack File: " << ptr.pack() << std::endl;
			std::cout << std::setw(20) << "Data: " << ptr.data() << std::endl;
		}
		else
		{
			std::cerr << "Could not find info for '" << argv[2] << "'" << std::endl;
		}
		return 0;
	}
	else
	{
		std::cout << "Usage: catalog <catalog> <path>" << std::endl;
		return 1;
	}
}
