#include "main.h"

int main(int argc, char* argv[]) {

  if(argc < 2) {
    std::cout << "Insufficient arguments supplied\n";
    return 1;
  }

  std::string name = argv[1];
  
  std::filesystem::path directory = std::filesystem::current_path();
  std::filesystem::path executablePath = std::filesystem::path(argv[0]).parent_path();

  std::cout << "Checking file structure\n";

  if(!(std::filesystem::exists(directory) && std::filesystem::is_directory(directory))) { 
    std::cout << "Invalid directory or doesn't exist: " << directory << "\n";
    return 1;
  }

  std::string filePath = "";

  findProjectFile(filePath, directory, executablePath);

  if(filePath == "") {
    std::cout << "The project.txt file could not be found\n";
    return 1;
  }

  CompileInfo info(filePath);

  Directory parentDir(directory);
  if(parentDir.fillSelf(info.excludes)) {
    std::cout << "Filling directory failed: " << directory << "\n";
    return 1;
  }

  if(createFile(parentDir, info, name)) {
    std::cout << "Failed to create file\n";
    return 1;
  }

}

void findProjectFile(std::string& filePath, std::filesystem::path& directory, std::filesystem::path& executablePath) {
  for(const auto& entry : std::filesystem::directory_iterator(directory)) {
    if (std::filesystem::is_regular_file(entry)) {
      if (entry.path().filename() == "project.txt") filePath = "project.txt";
    }
  }

  if(filePath == "") {
    // Check if the path is correct and iterate through the directory
    if(std::filesystem::exists(executablePath) && std::filesystem::is_directory(executablePath)) {
      for(const auto& entry : std::filesystem::directory_iterator(executablePath)) {
        if (std::filesystem::is_regular_file(entry)) {
          if(entry.path().filename() == "project.txt") filePath = entry.path().string();
        }
      }
      std::cout << "Could not find project.txt in current directory, using global project.txt \n";
    } else {
      std::cout << "Invalid directory or doesn't exist: " << executablePath << "\n";
      return;
    }
  }
}