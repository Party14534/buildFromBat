#include "getCompileInfo.h"

CompileInfo::CompileInfo(std::string fileLocation) {

  std::ifstream file(fileLocation);
  if(!file.is_open()) {
    std::cerr << "Could not open the file.\n";
    return;
  }

  std::unordered_map<std::string, std::vector<std::string>> map;
  std::string line;
  
  while(std::getline(file, line)) {
    size_t delimeterPos = line.find('=');
    if(delimeterPos != std::string::npos) {
      std::string key = line.substr(0, delimeterPos);
      std::string value = line.substr(delimeterPos + 1);
      map[key].push_back(value);
    }
  }

  file.close();

  for(const auto& pair : map) {
    if(pair.first == "compiler") { for(const auto& c : pair.second) compiler = c; }
    else if(pair.first == "flag") { for(const auto& f : pair.second) flags.push_back(f); }
    else if(pair.first == "includeDirectory") { for(const auto& iD : pair.second) includeDirectories.push_back(iD); }
    else if(pair.first == "libraryDirectory") { for(const auto& lD : pair.second) libraryDirectories.push_back(lD); }
    else if(pair.first == "library") { for(const auto& l : pair.second) libraries.push_back(l); }
    else if(pair.first == "exclude") { for(const auto& e : pair.second) excludes.push_back(e); }
  }

}