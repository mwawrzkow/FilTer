#include "FileHandler.h"
#include  <iostream>

using namespace std;



int main() {
    const char* env_p = std::getenv("HOME");
	Files::FileHandler Directory(env_p);
	std::cout << Directory.CheckAmountOfFiles();
}