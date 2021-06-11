#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

int ReadImageData(const std::filesystem::path &path, std::vector<uint16_t> &data) {
    std::ifstream fileStream(path);
    if (fileStream.is_open() == false) {
        std::cout << "Error, could not open file:" << path;
        return -1;
    }

    uint32_t xDimension = 0;
    uint32_t yDimension = 0;
    uint16_t bitDepth = 0;
    std::string magicNumber;
    std::string line;
    int lineIndex = 0;

    while (std::getline(fileStream, line))
    {
        if (line.at(0) == '#')
            break;

        std::stringstream lineStream(line);

        if(lineIndex == 0)
        {
            lineIndex++;
            lineStream >> magicNumber;
            std::cout << magicNumber << std::endl;
            continue;
        }
        if(lineIndex == 1)
        {
            lineIndex++;
            lineStream >> xDimension >> yDimension;
            std::cout << "X:" << xDimension << "Y:" << yDimension << std::endl;
            continue;
        }
        if (lineIndex == 2)
        {
            lineIndex++;
            lineStream >> bitDepth;
            std::cout << "bitDepth:" << bitDepth << std::endl;
            continue;
        }

        size_t pos = 0;
//        stringstream is almost twice slower as string parsing(below)
//        uint16_t token;
//        while(lineStream >> token){
//            data.push_back(token);
//        }
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
