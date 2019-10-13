#pragma once
#include "../FolderLocation/FileHandler.h"
#include "../ExtensionFilter/src/Filter.hpp"


class Handler{
    std::string HomeDir;
    yaml_reader config;
    Files::FileHandler IO;
    public:
    Handler(std::string);
    void loop();

};