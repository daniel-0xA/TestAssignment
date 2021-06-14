#pragma once

struct FileHeader {
    uint32_t xDimension = 0;
    uint32_t yDimension = 0;
    uint16_t bitDepth = 0;
    std::string magicNumber;
};

char* ParseArguments(int argc, char* argv[]);
int ReadFileHeader(const std::filesystem::path &path, FileHeader &header);
int ReadImageData(const std::filesystem::path &path, std::vector<uint32_t> &data);
