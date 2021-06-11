#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include "FileHeader.h"


int ReadImageData(const std::filesystem::path &path, std::vector<uint16_t> &data) {
    std::ifstream fileStream(path);
    if (fileStream.is_open() == false) {
        std::cout << "Error, could not open file:" << path;
        return -1;
    }

    std::string line;
    int lineIndex = 0;

    while (std::getline(fileStream, line))
    {
        if (line.at(0) == '#')
            break;

        if(lineIndex < 3) {
            lineIndex++;
            continue;
        }

//        stringstream is almost twice slower as string parsing
//        std::stringstream lineStream(line);
//        uint16_t token;
//        while(lineStream >> token){
//            data.push_back(token);
//        }

        size_t pos = 0;
        std::string token;
        while ((pos = line.find(' ')) != std::string::npos) {
            token = line.substr(0, pos);
            uint16_t value = std::stoul(token);
            data.push_back(value);
            line.erase(0, pos + 1);
        }

        lineIndex++;
    }
    return 0;
}

int ReadFileHeader(const std::filesystem::path &path, FileHeader &header) {
    std::ifstream fileStream(path);
    if (fileStream.is_open() == false) {
        std::cout << "Error, could not open file:" << path;
        return -1;
    }

    std::string line;
    int lineIndex = 0;

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream(line);
        if(lineIndex == 0)
        {
            lineIndex++;
            lineStream >> header.magicNumber;
//            std::cout << magicNumber << std::endl;
            continue;
        }
        if(lineIndex == 1)
        {
            lineIndex++;
            lineStream >> header.xDimension >> header.yDimension;
//            std::cout << "X:" << xDimension << "Y:" << yDimension << std::endl;
            continue;
        }
        if (lineIndex == 2)
        {
            lineIndex++;
            lineStream >> header.bitDepth;
//            std::cout << "bitDepth:" << bitDepth << std::endl;
            continue;
        }
        return 0;
    }

    return -1;
}
