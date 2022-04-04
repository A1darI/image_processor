#pragma once
#include "filter.h"

class SinglePixelFilter : public Filter {
public:
    Image Apply(const Image& image) const override;

private:
    virtual Pixel ChangePixel(const Pixel& pixel) const = 0;
};