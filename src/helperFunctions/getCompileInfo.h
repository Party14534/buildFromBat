#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

struct CompileInfo {
  std::string compiler;
  std::vector<std::string> flags;
  std::vector<std::string> includeDirectories;
  std::vector<std::string> libraryDirectories;
  std::vector<std::string> libraries;

  CompileInfo(std::string fileLocation);
};