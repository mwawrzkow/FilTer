#include "Handler.hpp"

Handler::Handler(std::string configFile):config(configFile){}

void Handler::loop(){

}

boid Handler::setConfigFile(std::string file){
    config = file;
}