#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include "FileHeader.h"


int ReadImageData(const std::filesystem::path &path, std::vector<uint32_t> &data) {
    std::ifstream fileStream(path);
    if (fileStream.is_open() == false) {
        std::cout << "Error, could not open file:" << path;
        return -1;
    }

    std::string line;
    int lineIndex = 0;
    uint32_t indexPixel = 0;

    while (std::getline(fileStream, line))
    {
        if (line.at(0) == '#')
            break;

        if(lineIndex < 3) {
            lineIndex++;
            continue;
        }

        size_t pos = 0;
        std::string token;
        while ((pos = line.find(' ')) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);

            uint32_t value = std::stoul(token);
            auto previousVal = data.at(indexPixel);
            data.at(indexPixel) = value + previousVal;
            indexPixel++;
        }

        lineIndex++;
    }
    return 0;
}

int ReadFileHeader(const std::filesystem::path &path, FileHeader &header) {
    std::ifstream fileStream(path);
    if (!fileStream.is_open()) {
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
            continue;
        }
        if(lineIndex == 1)
        {
            lineIndex++;
            lineStream >> header.xDimension >> header.yDimension;
            continue;
        }
        if (lineIndex == 2)
        {
            lineIndex++;
            lineStream >> header.bitDepth;
            continue;
        }
        return 0;
    }

    return -1;
}
