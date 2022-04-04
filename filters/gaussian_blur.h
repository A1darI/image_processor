#pragma once
#include "matrix_filter.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur(double sigma);
    Image Apply(const Image& image) const override;

private:
    using Dvector = std::vector<double>;

    static Dvector GetCoefficientArray(double sigma);
    static std::vector<Dvector> ReshapeToHeightMatrix(const Dvector& array);
    static std::vector<Dvector> ReshapeToWidthMatrix(const Dvector& array);

    const Dvector coefficient_array_;
    const MatrixFilter h_filter_;
    const MatrixFilter w_filter_;
};