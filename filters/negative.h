#pragma once
#include "single_pixel_filter.h"

class Negative : public SinglePixelFilter {
    Pixel ChangePixel(const Pixel& pixel) const override;
};