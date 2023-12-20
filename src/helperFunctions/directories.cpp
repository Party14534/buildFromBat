#include "directories.h"

// Directory
Directory::Directory(std::filesystem::path path) : path(path) { }

void Directory::addChildDirectory(std::filesystem::path childDirectory) {
  directories.push_back(
    std::make_unique<Directory>(childDirectory)
  );
}

void Directory::addChildFile(std::filesystem::path name, std::filesystem::path path) {
  files.push_back(
    std::make_unique<File>(name, path)
  );
}

void Directory::printDirectory(int indent) {
  if(indent == 0) std::cout << path.filename() << "\n";

  std::string tab = "    ";

  for(int i = 0; i < indent; i++) tab += "    ";

  tab += "- ";

  for(const auto& dir : directories) {
    std::cout << tab << dir->path.filename() << "\n";
    dir->printDirectory(indent + 1);
  }

  for(const auto& file : files) {
    std::cout << tab << file->name << "\n";
  }
}

int Directory::fillSelf(std::vector<std::string>& excludes) {

  // Check if the path is correct
  if(std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
    // Iterate through directory
    for(const auto& entry : std::filesystem::directory_iterator(path)) {
      if(std::filesystem::is_directory(entry)) {
        if(!inExcludes(excludes, entry.path().filename().string())) addChildDirectory(entry.path());
      } else if (std::filesystem::is_regular_file(entry)) {
        if(!inExcludes(excludes, entry.path().filename().string())) addChildFile(entry.path().filename(), entry.path());
      }
    }

  } else {
    std::cout << "Invalid directory or doesn't exist: " << path << "\n";
    return 1;
  }

  for(const auto& dir : directories) {
    dir->fillSelf(excludes);
  }

  return 0;

}

std::vector<std::string> Directory::getAllFiles() {
  std::vector<std::string> filePaths;

  for(const auto& file : files) {
    if(file->path.extension() == ".cpp")filePaths.push_back(file->path.string());
  }

  for(const auto& dir : directories) {
    std::vector<std::string> dirPaths = dir->getAllFiles();
    filePaths.insert(filePaths.end(), dirPaths.begin(), dirPaths.end());
  }

  return filePaths;
}

// Files
File::File(std::filesystem::path name, std::filesystem::path path) : name(name), path(path) { }

bool inExcludes(std::vector<std::string>& excludes, std::string filename) {
  for(const std::string& exclude : excludes) {
    if(filename == exclude) return true;
  }

  return false;
}