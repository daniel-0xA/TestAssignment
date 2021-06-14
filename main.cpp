#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include "FileHeader.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    auto timer1 = std::chrono::high_resolution_clock::now();

    char* folderPath = ParseArguments(argc, argv);
    if (!folderPath) {
        return -1;
    }

    // get the absolute path from the relative one
    const auto absoluteImgPath = fs::absolute(folderPath);
    if(!fs::exists(absoluteImgPath)) {
        std::cout << "Exit, path does not exist:" << absoluteImgPath <<std::endl;
        return -1;
    }

    // get all files in folder
    std::vector<fs::path> filePaths;
    for (const auto& entry : fs::directory_iterator(absoluteImgPath)) {
        // skip possible folder entries
        if (fs::is_directory(entry.path()))
            continue;

        filePaths.push_back(entry.path());
    }

    // prerequisite: all the files should have same header
    // read the header from the first file
    FileHeader header;
    if(ReadFileHeader(filePaths[0], header) == -1){
        std::cout << "Error getting image header.";
        return -1;
    }

    auto xyDimension = header.xDimension*header.yDimension;

    std::vector<unsigned int> pixelValues(xyDimension);
    for (const auto& path : filePaths) {
        if(ReadImageData(path, pixelValues) == -1){
            std::cout << "Error, could not open file:" << path;
            return -1;
        }
    }
    auto filesCount = filePaths.size();

    auto timer2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(timer2 - timer1);
    std::cout << "Data collection time:" << ms_int.count() << "ms\n";

    timer1 = std::chrono::high_resolution_clock::now();

    std::string outfilePath = absoluteImgPath.string() + "/average.pgm";
    std::ofstream outfile(outfilePath, std::ios_base::out | std::ios_base::binary);
    if (!outfile.is_open())
    {
        std::cout << "ERROR opening file:" << outfilePath << " errno:" << errno;
        return -1;
    }

    // write to average file the header and then the average values
    outfile << header.magicNumber << std::endl;
    outfile << header.xDimension << " " << header.yDimension << std::endl;
    outfile << header.bitDepth << std::endl;

    uint32_t indexWrite = 0;
    for (const auto& value : pixelValues)
    {
        indexWrite++;
        // divide the summation value to the number of files to get the arithmetic average/mean
        auto averageValue = value / filesCount;
        outfile << averageValue << " ";
        if (indexWrite % (header.xDimension) == 0)
        {
            outfile << std::endl;
            indexWrite = 0;
        }
    }

    timer2 = std::chrono::high_resolution_clock::now();
    ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(timer2 - timer1);
    std::cout << "Save to file time:" << ms_int.count() << "ms\n";

    // on my system, the metrics, for the given 10 files:
    // Data collection time:38476ms
    // Save to file time:6591ms

    return 0;
}