#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include "FileHeader.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();

    char* folderPath = ParseArguments(argc, argv);
    if (!folderPath) {
        return -1;
    }

    const auto absoluteImgPath = fs::absolute(folderPath);
    if(fs::exists(absoluteImgPath) == false) {
        std::cout << "Exit, path does not exist:" << absoluteImgPath <<std::endl;
        return -1;
    }

    std::vector<fs::path> filePaths;
    for (const auto& entry : fs::directory_iterator(absoluteImgPath)) {
        // skip possible folder entries
        if (fs::is_directory(entry.path()))
            continue;

        filePaths.push_back(entry.path());
    }

    struct FileHeader header;

    // prerequisite: all the files should have same header
    // read the header from the first file
    if(ReadFileHeader(filePaths[0], header) == -1){
        std::cout << "Error getting image header.";
        return -1;
    }
    auto xDimension = header.xDimension;//1856;
    auto yDimension = header.yDimension;//1024;
    auto xyDimension = xDimension*yDimension;

    std::vector<std::vector<uint16_t>> pixels;

    for (const auto& path : filePaths) {
        std::vector<uint16_t> data;
        if(ReadImageData(path, data) == -1){
            std::cout << "Error, could not open file:" << path;
            return -1;
        }
        pixels.push_back(data);
    }
    auto filesCount = pixels.size();

    std::vector<unsigned int> result(xyDimension);
    for (const auto& item : pixels) {
        unsigned int index = 0;
        for (const auto &value : item) {
            auto previousVal = result.at(index);
            result.at(index) = value + previousVal;
            index++;
        }
    }
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Data collection time:" << ms_int.count() << "ms\n";

    t1 = high_resolution_clock::now();

    std::string outfilePath = absoluteImgPath.string() + "./average.pgm";
    std::ofstream outfile(outfilePath, std::ios_base::out | std::ios_base::binary);
    if (outfile.is_open() == false)
    {
        std::cout << "ERROR opening file:" << outfilePath << " errno:" << errno;
        return -1;
    }

    outfile << header.magicNumber << std::endl;
    outfile << xDimension << " " << yDimension << std::endl;
    outfile << header.bitDepth << std::endl;

    uint16_t indexWrite = 0;
    for (const auto& value : result)
    {
        indexWrite++;
        // divide the summation value to the number of files to get the arithmetic average/mean
        auto averageValue = value / filesCount;
        outfile << averageValue << " ";
        if (indexWrite % (xDimension) == 0)
        {
            outfile << std::endl;
            indexWrite = 0;
        }
    }

    t2 = high_resolution_clock::now();
    ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Save to file time:" << ms_int.count() << "ms\n";

    return 0;
}