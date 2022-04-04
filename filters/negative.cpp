#include "negative.h"

Pixel Negative::ChangePixel(const Pixel& pixel) const {
    Pixel result_pixel;
    result_pixel.red = 255 - pixel.red;
    result_pixel.green = 255 - pixel.green;
    result_pixel.blue = 255 - pixel.blue;
    return result_pixel;
}