#pragma once
#include <vector>
#include <initializer_list>
#include <string>

namespace Filter{
class Folder {
public:
class Extension;
private:
std::vector<Extension> behavior;
std::vector<std::string> FileList;
public:
    Folder(std::initializer_list<Extension>);
    void saveFileList(std::initializer_list<std::string>);
    std::vector<std::tuple<std::string,std::string>> getOrderList();
public:
class Extension{
    std::vector<std::string> Extensions;
    bool changeName = false; 
    std::string ChangeNameTo; 
    std::string MoveTo;
    bool isForAll = false;
    public:
    Extension(std::string to, bool = true);
    Extension(std::initializer_list<std::string>,std::string,  bool = false);
    Extension(std::initializer_list<std::string>, std::string, bool,std::string);
    bool DoesExtensionMatch(std::string);
    bool DoesApplyToAllFiles();
    std::string NewFileLocation(std::string);
};






};






class yaml_reader{

};
}