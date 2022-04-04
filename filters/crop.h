#pragma once
#include "filter.h"

class Crop : public Filter {
public:
    Crop(int32_t height, int32_t width);
    Image Apply(const Image& image) const override;

private:
    const int32_t height_;
    const int32_t width_;
};