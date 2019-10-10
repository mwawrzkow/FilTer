#include "FileHandler.h"
#include <iostream>



namespace Files {
FileHandler::FileHandler(const std::string &path) : path(path){

}
std::vector<std::string> FileHandler::GetFiles()
{
boost::filesystem::path pth(this->path);
boost::filesystem::directory_iterator end_itr;
std::vector<std::string> Dirs;
for(boost::filesystem::directory_iterator itr(pth); itr!=end_itr; itr++ )
{
 Dirs.push_back(itr->path().string());
}
return Dirs;
}

}