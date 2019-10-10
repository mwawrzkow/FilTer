#include "Filter.hpp"
#include <functional>
#ifdef _WIN32
const static char shash = '\/';

#endif

#ifdef linux
const static char slash = '\\';
#endif

namespace Filter {
Folder::Folder(std::initializer_list<Extension> extensions) : behavior(extensions){

}

void Folder::saveFileList(std::initializer_list<std::string> List){
	FileList.clear();
	FileList = std::vector<std::string>(List);
}

std::vector<std::tuple<std::string,std::string> > Folder::getOrderList(){
	std::vector<std::tuple<std::string,std::string> > retVal;
	for(auto file : FileList) {
		for(auto interaction: behavior) {
			if(interaction.DoesExtensionMatch(file))
			{
				retVal.push_back(std::make_tuple(file, interaction.NewFileLocation(file)));
			}else if(interaction.DoesApplyToAllFiles())
			{
				retVal.push_back(std::make_tuple(file,interaction.NewFileLocation(file)));
			}

		}
	}
	return retVal;
}
Folder::Extension::Extension(std::initializer_list<std::string> List, std::string moveTo, bool changeName, std::string ChangeTo)
	: Extensions(List),
	MoveTo(moveTo),
	ChangeNameTo(ChangeTo),
	changeName(changeName),
	isForAll(false){
}
Folder::Extension::Extension(std::string To, bool isForAll)
	: isForAll(isForAll),
	MoveTo(To){
}
Folder::Extension::Extension(std::initializer_list<std::string>List,std::string to,  bool ChangeName)
	: Extensions(List),
	MoveTo(to),
	changeName(ChangeName),
	ChangeNameTo(NULL),
	isForAll(false)
{
}
bool Folder::Extension::DoesExtensionMatch(std::string extension){
	for(auto e: Extensions) {
		if(e == extension) {
			return true;
		}
	}
	return false;
}
bool Folder::Extension::DoesApplyToAllFiles()
{
	return this->isForAll;
}

std::string Folder::Extension::NewFileLocation(std::string file){

}


}

