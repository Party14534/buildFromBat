#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <memory>

bool inExcludes(std::vector<std::string>&, std::string);

struct File {
  std::filesystem::path name;
  std::filesystem::path path;
  File(std::filesystem::path name, std::filesystem::path path);
};

struct Directory {
  std::filesystem::path path;
  std::vector<std::unique_ptr<Directory>> directories;
  std::vector<std::unique_ptr<File>> files;

  Directory(std::filesystem::path);
  void addChildDirectory(std::filesystem::path childDirectory);
  void addChildFile(std::filesystem::path name, std::filesystem::path path);
  void printDirectory(int indent = 0);
  int fillSelf(std::vector<std::string>& excludes);
  std::vector<std::string> getAllFiles();
};