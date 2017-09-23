#include <iostream>

#include <assembly/filesystem.hpp>

#include "pack_cli.hpp"
#include "fdb_cli.hpp"
#include "pipe_cli.hpp"
#include "cli.hpp"

#include "../config.h"

// Declare ahead
int main_test(int argc, char** argv);
int main_help(int argc, char** argv);

cli::opt_t main_options[] =
{
	{	"pipe",		&main_pipe, 	"Manipulate files in stages"	},
	{	"catalog", 	&main_catalog,	"Show file info in a catalog"	},
	{	"pack", 	&main_pack, 	"Manipulate pack archives"		},
	{	"fdb",		&main_fdb, 		"Manipulate a FileDataBase"		},
	{	"test",		&main_test, 	"Test some stuff"				},
	{	"help",		&main_help, 	"Show this help"				},

	{0,0,0}
};

int main(int argc, char** argv) {

	if (argc == 1)
	{
		std::cout << "Usage: <subcommand> ..." << std::endl;
		return 1;
	}

	return cli::call(PACKAGE_NAME, main_options, argv[1], argc - 1, argv + 1);
}

int main_help(int argc, char** argv)
{
	return cli::help(PACKAGE_NAME, main_options, "Developer Tool for LEGO Universe");
}

int main_test(int argc, char** argv)
{
	fs::path pth = fs::path("/usr/include");
	fs::path pth2 = fs::path(pth).append("assembly").append("filesystem.hpp");

	std::cout << pth.to_string() << std::endl;
	std::cout << pth2.to_string() << std::endl;
	return 0;
}
