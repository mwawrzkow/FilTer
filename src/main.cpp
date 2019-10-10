#include "Handler/Handler.hpp"
#include  <iostream>


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


int main() {
    const char* env_p = std::getenv("HOME");
	
	
}