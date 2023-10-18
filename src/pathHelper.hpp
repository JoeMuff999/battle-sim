#pragma once

#include <string>

#ifdef _WIN32
// Windows-specific headers
#include <direct.h>
#define GetCurrentDir _getcwd
#else
// Linux-specific headers
#include <unistd.h>
#include <limits.h>
#define GetCurrentDir getcwd
#endif

class PathHelper
{
public: 
    static const std::string generatePath(std::string path)
    {
        char cwd[FILENAME_MAX];
        GetCurrentDir(cwd, FILENAME_MAX);

        std::string currDir(cwd);
        currDir += path;

        return currDir;
    }
};