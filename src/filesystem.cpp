#include "filesystem.hpp"

#include <sys/stat.h>
#include <cstdio>


int create_directory(std::string path)
{
	return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

bool exists(std::string path) {
	struct stat sts;
	if (stat(path.c_str(), &sts) == -1 && errno == ENOENT)
	{
	    return false;
	}
	return true;
}

void ensure_dir_exists(std::string path) {
	int index = path.find_last_of('/');
	if (index > 0) {
		std::string dir(path.substr(0, index));
		if (!exists(dir)) {
			ensure_dir_exists(dir);
			create_directory(dir);
		}
	}
}