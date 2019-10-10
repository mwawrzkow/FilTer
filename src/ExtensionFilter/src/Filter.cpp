#include "Filter.hpp"
#include <functional>
#include <iostream>
#ifdef _WIN32
const static char shash = '\/';

#endif

#ifdef linux
const static char slash = '\\';
#endif

namespace Filter {
Folder::Folder(std::vector<Extension> extensions) : behavior(extensions){

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
Folder::Extension::Extension(std::vector<std::string> List, std::string moveTo, bool changeName, std::string ChangeTo)
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

yaml_reader::yaml_reader(std::string filename):FileLoc(filename){
	YAML::Node config = YAML::LoadFile(filename);
	int mode; 
	if(config["mode"]){
		mode = config["mode"].as<int>();
	}
	switch(static_cast<yaml_reader::Type>(mode))
	{
		case Type::FindFile:
		 addConfig(config["alias"]);
		break;
		case Type::SetFile:
			setConfigs(config["settings"]);
		break;
		default:
		throw std::logic_error("Not Supported Type");
		break;
	}
}

void yaml_reader::addConfig(YAML::Node  node){
	for(std::size_t i = 0 ; i < node.size(); ++i)
		Configs.push_back(yaml_reader(node[i].as<std::string>()));
}

void yaml_reader::setConfigs(YAML::Node node){
	std::vector<Filter::Folder::Extension> List;
	for(const auto &e : node)
	{
		std::vector<std::string> extensions;
		std::string shouldMove;
		for(const auto &c : node["Extensions"])
			extensions.push_back(c.as<std::string>());
		if(e["MoveToDir"])
		{
			shouldMove = e["MoveToDir"].as<std::string>();
		}else{
			throw std::logic_error("Not Supported File");
		}
		bool changeName = false;
		if(e["Rename"]){
			changeName = e["Rename"].as<bool>();
		}
		std::string newName;
		if(e["Rename_To_Name"]){
			newName = e["Rename_To_Name"].as<std::string>();
		}
		List.push_back(Filter::Folder::Extension(extensions,shouldMove,changeName,newName));
	}
	
	Folder.reset(new std::tuple<std::string,Filter::Folder>(FileLoc,Filter::Folder(List)));
}
std::vector<std::tuple<std::string, Filter::Folder>> yaml_reader::getWatchDog(){
	std::vector<std::tuple<std::string,Filter::Folder>> retVal;
	for(auto &c : Configs)
	{
		auto tmp = c.getWatchDog();
		for(auto &d: tmp)
		{
			if(std::get<0>(d) != "NULL")
				retVal.push_back(d);
		}
	}
	if(Folder != nullptr)
	{
		retVal.push_back(*Folder);
	}
	return retVal;
}
