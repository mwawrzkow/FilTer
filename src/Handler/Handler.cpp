#include "Handler.hpp"
#include <iostream>
Handler::Handler(std::string configFile):config(configFile){}

void Handler::loop(){
auto list = config.getWatchDog();
for(auto &e: list){
    IO.setpath(std::get<0>(e));
    auto FileList = IO.GetFiles();
    std::get<1>(e).saveFileList(FileList);

    auto Orders = std::get<1>(e).getOrderList();
    for(auto &c: Orders)
    {
        IO.MoveFile(std::get<0>(c),std::get<1>(c));
    }
}
}

