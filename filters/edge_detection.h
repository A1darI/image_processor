#pragma once
#include "matrix_filter.h"
#include "grayscale.h"
#include "single_pixel_filter.h"

class BoundaryFilter : public SinglePixelFilter {
public:
    BoundaryFilter(double threshold);

private:
    Pixel ChangePixel(const Pixel& pixel) const override;
    uint8_t threshold_;
};

class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);
    Image Apply(const Image &image) const override;

private:
    const GrayScale grayscale_;
    const MatrixFilter matrix_filter_;
    const BoundaryFilter boundary_filter_;
};