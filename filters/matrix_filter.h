#pragma once
#include "filter.h"

class MatrixFilter : public Filter {
public:
    MatrixFilter(const std::vector<std::vector<double>>& matrix);
    Image Apply(const Image& prepared_image) const override;

private:
    const int32_t h_radius_;
    const int32_t w_radius_;
    const std::vector<std::vector<double>> matrix_;
};
