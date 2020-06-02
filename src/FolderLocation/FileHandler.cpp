#include "FileHandler.h"
#include <iostream>

namespace Files
{
    FileHandler::FileHandler(const std::string &path) : path(path)
    {
    }
    FileHandler::FileHandler() {}
    void FileHandler::setpath(const std::string &path)
    {
        this->path = path;
    }

    std::vector<std::string> FileHandler::GetFiles()
    {
        std::vector<std::string> Dirs;
        if (boost::filesystem::is_directory(this->path))
        {
            boost::filesystem::path pth(this->path);
            boost::filesystem::directory_iterator end_itr;

            for (boost::filesystem::directory_iterator itr(pth); itr != end_itr; itr++)
            {
                Dirs.push_back(itr->path().string());
            }
        }
        return Dirs;
    }
    bool FileHandler::MoveFile(std::string from, std::string to)
    {
        std::string Adress = resolve(to);
        boost::filesystem::path pth(Adress);
        boost::filesystem::directory_iterator end_itr;
        std::vector<std::string> Dirs;
        int rerename = 0;
        std::string tofinal = to;
        for (boost::filesystem::directory_iterator itr(pth); itr != end_itr; itr++)
        {
            if (itr->path().string() == tofinal)
            {
                rerename++;
                std::string tmpname = to;
                std::size_t where = tmpname.find_last_of(".");
                std::string extension = tmpname.substr(where, tmpname.size());
                tmpname.erase(tmpname.begin() + where, tmpname.end());
                tofinal = tmpname + std::to_string(rerename) + extension;
                itr = boost::filesystem::directory_iterator(pth);
            }
        }
        //Deletes the extension
        boost::filesystem::rename(from, tofinal);
    }
    std::string FileHandler::resolve(std::string file)
    {
        //https://github.com/mwawrzkow/colo/blob/master/src/FileIOController.h#L11
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        const char slash = 0x5C;

#else
        const char slash = 0x2F;

#endif

        std::string s = file;
        std::size_t whereami;
        whereami = s.find_last_of(slash);
        s.erase(s.begin() + (whereami + 1), s.end());
        return s;
    }

} // namespace Files
