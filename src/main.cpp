#include <cxxopts.hpp>
#include "Handler/Handler.hpp"
#include  <iostream>
#include <thread>
#include <chrono>
#include <atomic>
//TODO: Create GUI
static int InterVal = 5; 
static std::atomic<bool> _EXIT(false);
static std::atomic<bool> __DoesThreadWorks(true);
//https://github.com/mwawrzkow/colo/blob/master/src/FileIOController.h#L11
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
const char slash = 0x5C;

#else
const char slash = 0x2F;

#endif
// https://github.com/mwawrzkow/colo/blob/master/src/FileIOController.cpp#L10
namespace FileIO {

int lastslash(char findchar, std::string ourstring) {
	std::size_t temp;
	temp = ourstring.find_last_of(findchar);
	return temp;
}
void getexepath(const std::string exeLocation, std::string &filelocation) {
	filelocation = exeLocation;
	std::size_t whereami = lastslash(slash, filelocation);
	filelocation.erase(filelocation.begin() + (whereami + 1),
			filelocation.end());
}

} /* namespace FileIO */
void ThreadLoop(std::reference_wrapper<Handler> handle)
	{
	__DoesThreadWorks = true;
	auto x1 = std::chrono::system_clock::now();
	do{
	handle.get().loop();
	x1 = std::chrono::system_clock::now();
	if(_EXIT)
	{
		__DoesThreadWorks = false;
		return;
	}
	std::this_thread::sleep_for(std::chrono::seconds(InterVal));
	}while(true);
	}
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//!Pass
#else
cxxopts::Options options("FilTer", "The Files sorter");
void noGui(std::string);
void Gui(std::string);
void LoadDefaultSettings(std::string&);
int main(int argc,char *argv[]) {

    std::string mainConfig;
    options.add_options()
	    ("q,quiet", "quiet run")
	    ("f,file", "absolute config location", cxxopts::value<std::string>());
    auto results = options.parse(argc,argv);
    if(results.count("q") != 1 )
    {
	if(results.count("f") != 1){
	LoadDefaultSettings(mainConfig);
	Gui(mainConfig);
	}
	else
	Gui(results["f"].as<std::string>());
    }else{
    	if(results.count("f") !=  1){
		return EXIT_FAILURE;
    	}
	if(results["q"].as<bool>()){
	try{
		noGui(results["f"].as<std::string>());
	}catch(cxxopts::OptionException& e){
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
	}
    }


	//TODO: Create Handler Loop 
	
	return EXIT_SUCCESS;
}
void LoadDefaultSettings(std::string& DefaultConfigLocation)
{
    const char* env_p = std::getenv("HOME");
    DefaultConfigLocation = std::string(env_p);
	DefaultConfigLocation += "/.config.yaml";
}
void Gui(std::string Config){

	Handler Handle(Config);
	std::thread handlerThread(ThreadLoop,std::ref(Handle));
	Handle.loop();
	std::string command;
	do{
		std::cout << "\x1B[94m>>>\033[0m"; 
		std::getline(std::cin,command);
		if(command == "exit"){
		_EXIT = true;
		handlerThread.join();
		}
	}while(__DoesThreadWorks);
}
void noGui(std::string config){
std::vector<int> a;



}
#endif
