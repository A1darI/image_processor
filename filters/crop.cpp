#include "crop.h"

Crop::Crop(int32_t height, int32_t width) : height_(height), width_(width) {
}
Image Crop::Apply(const Image& image) const {
    Image result_image(std::min(height_, image.GetHeight()), std::min(width_, image.GetWidth()));
    int32_t h_offset = 0;
    if (result_image.GetHeight() < image.GetHeight()) {
        h_offset = image.GetHeight() - result_image.GetHeight();
    }
    for (int32_t y = 0; y < result_image.GetHeight(); ++y) {
        for (int32_t x = 0; x < result_image.GetWidth(); ++x) {
            result_image.SetPixel(x, y, image.GetPixel(x, y + h_offset));
        }
    }
    return result_image;
}