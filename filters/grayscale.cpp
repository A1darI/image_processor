#include "grayscale.h"

Pixel GrayScale::ChangePixel(const Pixel& pixel) const {
    uint8_t grayscale = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
    return {grayscale, grayscale, grayscale};
}