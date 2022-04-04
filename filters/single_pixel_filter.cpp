#include "single_pixel_filter.h"

Image SinglePixelFilter::Apply(const Image& image) const {
    Image result_image(image.GetHeight(), image.GetWidth());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            result_image.SetPixel(x, y, ChangePixel(image.GetPixel(x, y)));
        }
    }
    return result_image;
}