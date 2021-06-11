#include <algorithm>
#include <iostream>
#include <string>

char* getCmdOption(char** begin, char** end, const std::string& option)
{
    char** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

char* ParseArguments(int argc, char* argv[]) {
    // check for '-h' option
    if (cmdOptionExists(argv, argv + argc, "-h")) {
        std::cout << "with '-d' option provide the folder relative path (relative to where the executable is located) for the image files(e.g.: Imagees)";
        return 0;
    }

    char* folderPath = getCmdOption(argv, argv + argc, "-d");
    if (!folderPath) {
        std::cout << "The path to the image files not provided in the command line. For getting help use: '-h'.";
        return 0;
    }

    return folderPath;
}