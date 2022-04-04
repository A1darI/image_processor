#include <iostream>
#include "image.h"

int32_t Image::GetWidth() const {
    return width_;
}
int32_t Image::GetHeight() const {
    return height_;
}
Image::Image(int32_t height, int32_t width)
    : height_(height), width_(width), image_(std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width))) {
}
void Image::SetPixel(int32_t x, int32_t y, const Pixel& pixel) {
    image_[y][x] = {.red = pixel.red, .green = pixel.green, .blue = pixel.blue};
}
Pixel Image::GetPixel(int32_t x, int32_t y) const {
    if (y < 0) {
        y = 0;
    }
    if (y >= height_) {
        y = height_ - 1;
    }
    if (x < 0) {
        x = 0;
    }
    if (x >= width_) {
        x = width_ - 1;
    }
    return image_[y][x];
}