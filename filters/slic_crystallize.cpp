#include "slic_crystallize.h"
#include "image_slic_clustering.h"

Crystallize::Crystallize(int32_t superpixels_number, double compactness)
    : number_of_clusters_(superpixels_number), compactness_(compactness) {
}
Image Crystallize::Apply(const Image& image) const {
    ImageClustering image_clustering(image, number_of_clusters_, compactness_);
    size_t iteration = 0;
    double error = 100;
    while (iteration < max_iterations_ && error > error_) {
        image_clustering.ReinitializeClusterGrid();
        error = image_clustering.ReinitializeSuperpixels();
        ++iteration;
    }
    return image_clustering.GetImage(have_edges_);
}
