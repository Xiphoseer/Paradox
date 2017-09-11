#include "cli.hpp"

#include <cstring>
#include <cstdio>

int call(const char* cli, opt_t* options, const char* cmd, int argc, char** argv)
{
	for (opt_t* o = options; o->text != 0; o++)
	{
		if (strcmp(o->text, cmd) == 0)
		{
			return (*(o->func))(argc, argv);
		}
	}

	printf("%s command '%s' not found\n", cli, argv[0]);
	return 2;
}