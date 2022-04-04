#pragma once
#include "single_pixel_filter.h"

class GrayScale : public SinglePixelFilter {
    Pixel ChangePixel(const Pixel& pixel) const override;
};
