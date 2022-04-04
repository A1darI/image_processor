#include "reader.h"
#include <fstream>
#include "exceptions.h"

const size_t DIB_HEADER_START_OFFSET = 14;
const size_t DATA_SIZE = 4;
const int32_t PIXEL_ARRAY_STARTS_OFFSET = 54;

template <typename T>
void FRead(std::ifstream &file, T &number) {
    file.read(reinterpret_cast<char *>(&number), sizeof(number));
}

Image file_handling::Read(const std::string &file) {
    std::ifstream input(file, std::ios::in | std::ios::binary);
    if (input.is_open()) {
        input.seekg(DIB_HEADER_START_OFFSET, std::ios::cur);
        input.seekg(DATA_SIZE, std::ios::cur);  // skip DIB Header size
        int32_t width;
        int32_t height;
        FRead(input, width);
        FRead(input, height);
        Image result_image = Image(height, width);
        int32_t padding = GetPadding(result_image);
        input.seekg(PIXEL_ARRAY_STARTS_OFFSET, std::ios::beg);
        for (int32_t y = 0; y < height; ++y) {
            for (int32_t x = 0; x < width; ++x) {
                Pixel pixel;
                FRead(input, pixel.blue);
                FRead(input, pixel.green);
                FRead(input, pixel.red);
                result_image.SetPixel(x, y, pixel);
            }
            input.seekg(padding, std::ios::cur);
        }
        input.close();
        return result_image;
    } else {
        throw FileOpenFailedException(file);
    }
}