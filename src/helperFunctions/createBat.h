#include <iostream>
#include <fstream>
#include <filesystem>
#include "directories.h"
#include "getCompileInfo.h"

int createFile(Directory& parentDirectory, CompileInfo& info, std::string name);

int createDirectory(std::filesystem::path& buildPath);