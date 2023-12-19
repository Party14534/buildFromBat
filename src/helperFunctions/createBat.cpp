#include "createBat.h"

int createFile(Directory& parentDirectory, CompileInfo& info, std::string name) {

  std::filesystem::path buildPath;

  for(const auto& dir : parentDirectory.directories) {
    if(dir->path == "build") { 
      buildPath = dir->path;
      break;
    }
  }

  if(buildPath.empty())  {
    // return error if you cannot create a directory
    if(createDirectory(buildPath)) return 1; 
  }

  std::string filename = buildPath.filename().string() + "/build.bat";

  std::ofstream buildFile(filename);

  if (buildFile.is_open()) {
        // File is opened successfully, so write to it
        buildFile << info.compiler + " ";

        if(info.flags.size()) {
          for(const auto& flag : info.flags) {
            buildFile << "-" << flag << " ";
          }
        }

        if(info.includeDirectories.size()) {
          for(const auto& iDir : info.includeDirectories) {
            buildFile << "-I\""<< iDir << "\" ";
          }
        }

        if(info.libraryDirectories.size()) {
          for(const auto& lDir : info.libraryDirectories) {
            buildFile << "-L\""<< lDir << "\" ";
          }
        }

        buildFile << "^\n";

        std::vector<std::string> paths = parentDirectory.getAllFiles();
        for(const auto& path : paths) {
          buildFile << path + " ^\n";
        }

        buildFile << "-o build/" + name + " ";

        if(info.libraries.size()) {
          for(const auto& lib : info.libraries) {
            buildFile << "-l"<< lib << " ";
          }
        }

        buildFile << "\n";
        
        buildFile.close();
        std::cout << "File created successfully.\n";
    } else {
        // Failed to open the file
        std::cerr << "Failed to create the file!\n";
        return 1;
    }

    return 0;

}

int createDirectory(std::filesystem::path& buildPath) {
  std::filesystem::path dirPath = "build";

  try {
      if (std::filesystem::create_directory(dirPath)) {
          std::cout << "Directory created successfully.\n";
      } else {
          std::cout << "Directory creation failed or already exists.\n";
      }
  } catch (const std::filesystem::filesystem_error& e) {
      std::cerr << "Exception caught: " << e.what() << "\n";
      return 1;
  }

  buildPath = dirPath;

  return 0;
}