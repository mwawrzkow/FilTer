#pragma once
#include "../FolderLocation/FileHandler.h"
#include "../FileHolder/Holder.h"
#include "../ExtensionFilter/src/Filter.hpp"


class Handler{
    std::string HomeDir;
    yaml_reader config;
    public:
    Handler(std::string);
};