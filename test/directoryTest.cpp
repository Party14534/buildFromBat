#include "../src/helperFunctions/createBat.h"
#include <cassert>

bool testExcludeDirectory() {
  Directory dir(std::filesystem::current_path());

  std::ofstream buildFile("build/testProjectFile.txt");
  if (buildFile.is_open()) {
    buildFile << "exclude=testDirectory\n";
    buildFile << "exclude=build\n";
  }
  buildFile.close();

  CompileInfo info("build/testProjectFile.txt");

  dir.fillSelf(info.excludes);

  assert(info.excludes.size() == 2);
  assert(dir.directories.size() == 0);
  assert(dir.files.size() == 2);

  return true;
}

bool testExcludeFile() {
  Directory dir(std::filesystem::current_path());

  std::ofstream buildFile("build/testProjectFile.txt");
  if (buildFile.is_open()) {
    buildFile << "exclude=testFile.txt\n";
    buildFile << "exclude=build\n";
  }
  buildFile.close();

  CompileInfo info("build/testProjectFile.txt");

  dir.fillSelf(info.excludes);

  assert(info.excludes.size() == 2);
  assert(dir.directories.size() == 1);
  assert(dir.files.size() == 1);
  assert(dir.directories[0]->files.size() == 0);

  return true;
}

int main() {
  // Run the tests
  assert(testExcludeDirectory());
  assert(testExcludeFile());

  return 0;
}