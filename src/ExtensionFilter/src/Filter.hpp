#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include <yaml-cpp/yaml.h>
#include <stdexcept>

namespace Filter{
class Folder {
public:
class Extension;
private:
std::vector<Extension> behavior;
std::vector<std::string> FileList;
public:
    Folder(std::vector<Extension>);
    void saveFileList(std::vector<std::string>);
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
    Extension(std::vector<std::string>, std::string, bool,std::string);
    bool DoesExtensionMatch(std::string);
    bool DoesApplyToAllFiles();
    std::string NewFileLocation(std::string);
};






};





}
class yaml_reader{
    protected:
    std::shared_ptr<std::tuple<std::string,Filter::Folder>> Folder;
    std::vector<yaml_reader>Configs;
    std::string FileLoc;
    void addConfig(YAML::Node);
    void setConfigs(YAML::Node);
    public:
    yaml_reader(std::string);
    std::vector<std::tuple<std::string, Filter::Folder>> getWatchDog();
    private:
    enum Type{
        FindFile,
        SetFile
    };
};
