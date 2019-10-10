#pragma once
#include <string>
#include "boost/filesystem.hpp"




namespace Files {
class FileHandler {
std::string path;
protected:
public:
explicit FileHandler(const std::string &path);
std::vector<std::string> GetFiles(); 





};
}