#pragma once

#define CLI_PATH "cli"

namespace cli
{
	typedef int (*main_t) (int, char**);

	typedef struct
	{
		const char* text;
		main_t func;
		const char* help;
	}
	opt_t;

	int call(const char* cli, const opt_t* options, const char* cmd, int argc, char** argv);
	int help(const char* cli, const opt_t* options, const char* desc);
}
