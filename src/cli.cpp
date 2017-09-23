#include "cli.hpp"

#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>

int cli::call(const char* cli, const opt_t* options, const char* cmd, int argc, char** argv)
{
	for (const opt_t* o = options; o->text != 0; o++)
	{
		if (strcmp(o->text, cmd) == 0)
		{
			return (*(o->func))(argc, argv);
		}
	}

	printf("%s: command '%s' not found\n", cli, argv[0]);
	return 2;
}

int cli::help(const char* cli, const opt_t* options, const char* desc)
{
	std::cout << std::string(25, '=') << " " << cli << " Tool " << std::string(25, '=') << std::endl;
	std::cout << desc << std::endl;
	std::cout << std::endl << std::left;

	for (const opt_t* o = options; o->text != 0; o++)
	{
		if (o->help != 0)
		{
			std::cout << "  " << std::setw(15) << o->text << ": " << o->help << std::endl;
		}
	}

	std::cout << std::right << std::endl;
	std::cout << std::string(57 + strlen(cli), '=') << std::endl;

	return 0;
}