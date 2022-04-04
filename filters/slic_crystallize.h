#pragma once
#include "filter.h"

class Crystallize : public Filter {
public:
    Crystallize(int32_t superpixels_number, double compactness);
    Image Apply(const Image &image) const override;

private:
    int32_t number_of_clusters_;
    double compactness_;
    size_t max_iterations_ = 10;
    double error_ = 3;
    double have_edges_ = true;
};
