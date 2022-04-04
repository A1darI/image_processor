#include "edge_detection.h"

const Pixel BLACK_PIXEL = {0, 0, 0};
const Pixel WHITE_PIXEL = {255, 255, 255};

BoundaryFilter::BoundaryFilter(double threshold) : threshold_(threshold * 255.0) {
}

Pixel BoundaryFilter::ChangePixel(const Pixel& pixel) const {
    if (pixel.red > threshold_) {
        return WHITE_PIXEL;
    }
    return BLACK_PIXEL;
}

EdgeDetection::EdgeDetection(double threshold)
    : matrix_filter_({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), boundary_filter_(threshold) {
}
Image EdgeDetection::Apply(const Image& image) const {
    return boundary_filter_.Apply(matrix_filter_.Apply(grayscale_.Apply(image)));
}
