#pragma once
#include <string>

int create_directory(std::string path);

bool exists(std::string path);

void ensure_dir_exists(std::string path);