#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>

namespace fs = std::filesystem;

extern char* ParseArguments(int argc, char* argv[]);
extern int ReadImageData(const std::filesystem::path &path, std::vector<uint16_t> &data);

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

    std::string outfilePath("./MeanImage.pgm");
    std::ofstream outfile(outfilePath, std::ios_base::out | std::ios_base::binary);
    if (outfile.is_open() == false)
    {
        std::cout << "ERROR opening file:" << outfilePath << " errno:" << errno;
        return -1;
    }

    auto xDimension = 1856;
    auto yDimension = 1024;
    auto xyDimension = xDimension*yDimension;

    std::vector<fs::path> filePath;
    std::vector<std::vector<uint16_t>> pixels;

    // iterate files in folder
    for (const auto& entry : fs::directory_iterator(absoluteImgPath)) {
        // skip possible folder entries
        if(fs::is_directory(entry.path()))
            continue;

        filePath.push_back(entry.path());
        std::cout << entry.path() << std::endl;

        std::vector<uint16_t> data;//data(xyDimension);
        if( ReadImageData(entry.path(), data) == -1){
            std::cout << "Error, could not open file:" << entry.path();
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
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";

    outfile << "P2" << std::endl;
    outfile << xDimension << " " << yDimension << std::endl;
    outfile << 4096 << std::endl;

    uint16_t indexWrite = 0;
    for (const auto& value : result)
    {
        indexWrite++;
        auto meanValue = value/filesCount;
        outfile << meanValue << " ";
        if (indexWrite % (xDimension) == 0)
        {
            //std::cout << meanValue << std::endl;
            outfile << std::endl;
            indexWrite = 0;
        }
    }

    return 0;
}




