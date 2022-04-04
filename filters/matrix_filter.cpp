#include "matrix_filter.h"

MatrixFilter::MatrixFilter(const std::vector<std::vector<double>>& matrix)
    : h_radius_(matrix.size() / 2), w_radius_(matrix[0].size() / 2), matrix_(matrix) {
}

Image MatrixFilter::Apply(const Image& image) const {
    Image result_image(image.GetHeight(), image.GetWidth());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int32_t h_offset = 0; h_offset <= 2 * h_radius_; ++h_offset) {
                for (int32_t w_offset = 0; w_offset <= 2 * w_radius_; ++w_offset) {
                    Pixel current_pixel = image.GetPixel(x + w_offset - w_radius_, y - h_offset + h_radius_);
                    red += matrix_[h_offset][w_offset] * current_pixel.red;
                    green += matrix_[h_offset][w_offset] * current_pixel.green;
                    blue += matrix_[h_offset][w_offset] * current_pixel.blue;
                }
            }
            Pixel result_pixel;
            result_pixel.red = std::max(0.0, std::min(255.0, red));
            result_pixel.green = std::max(0.0, std::min(255.0, green));
            result_pixel.blue = std::max(0.0, std::min(255.0, blue));
            result_image.SetPixel(x, y, result_pixel);
        }
    }
    return result_image;
}
