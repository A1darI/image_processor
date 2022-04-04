#include "gaussian_blur.h"
#include <math.h>

Image GaussianBlur::Apply(const Image& image) const {
    Image w_blur_image = w_filter_.Apply(image);
    Image result_image = h_filter_.Apply(w_blur_image);
    return result_image;
}

GaussianBlur::GaussianBlur(double sigma)
    : coefficient_array_(GetCoefficientArray(sigma)),
      h_filter_(ReshapeToHeightMatrix(coefficient_array_)),
      w_filter_(ReshapeToWidthMatrix(coefficient_array_)) {
}
GaussianBlur::Dvector GaussianBlur::GetCoefficientArray(double sigma) {
    double sigma_expression = 2 * sigma * sigma;
    double coefficient_sum = 0;
    int32_t radius = 3 * sigma + 2;
    Dvector result_vector(2 * radius + 1);
    for (size_t i = 0; i < result_vector.size(); ++i) {
        result_vector[i] = exp(-(((i - radius) * (i - radius)) / sigma_expression));
        coefficient_sum += result_vector[i];
    }
    for (size_t i = 0; i < result_vector.size(); ++i) {
        result_vector[i] /= coefficient_sum;
    }
    return result_vector;
}
std::vector<GaussianBlur::Dvector> GaussianBlur::ReshapeToHeightMatrix(const GaussianBlur::Dvector& array) {
    std::vector<Dvector> result_vector(array.size(), Dvector(1));
    for (size_t i = 0; i < array.size(); ++i) {
        result_vector[i][0] = array[i];
    }
    return result_vector;
}
std::vector<GaussianBlur::Dvector> GaussianBlur::ReshapeToWidthMatrix(const GaussianBlur::Dvector& array) {
    std::vector<Dvector> result_vector(1, array);
    return result_vector;
}
