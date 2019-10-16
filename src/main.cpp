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
	if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - x1).count() > InterVal)
	{
	handle.get().loop();
	x1 = std::chrono::system_clock::now();
	}
	if(_EXIT)
	{
		__DoesThreadWorks = false;
		return;
	}
	}while(true);
	}
int main() {
    const char* env_p = std::getenv("HOME");
	std::string abc(env_p);
	abc += "/.config.yaml";

	//TODO: Create Handler Loop 
	Handler Handle(abc);
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
	
	return 0;
}
