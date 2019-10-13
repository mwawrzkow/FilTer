#pragma once
#include <string>
#include "boost/filesystem.hpp"




namespace Files {
class FileHandler {
std::string path;
protected:
std::string resolve(std::string);
public:
explicit FileHandler(const std::string &path);
explicit FileHandler();
void setpath(const std::string &path);
std::vector<std::string> GetFiles(); 
bool MoveFile(std::string, std::string );





};
}