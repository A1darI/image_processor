#pragma once
#include <cstdint>
#include <vector>

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class Image {
public:
    Image(int32_t height, int32_t width);
    void SetPixel(int32_t x, int32_t y, const Pixel& pixel);
    Pixel GetPixel(int32_t x, int32_t y) const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

private:
    int32_t height_;
    int32_t width_;
    std::vector<std::vector<Pixel>> image_;
};