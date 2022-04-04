#include "../image.h"
#include "math.h"

class ImageClustering {
public:
    ImageClustering(const Image& image, int32_t number_of_clusters, double compactness);

    void ReinitializeClusterGrid();
    double ReinitializeSuperpixels();
    Image GetImage(bool have_edges) const;

    struct PixelInImage {
        Pixel pixel = {0, 0, 0};
        int32_t y = 0;
        int32_t x = 0;

        bool operator==(const PixelInImage& pixel_in_image) const;
    };

    struct ClusterGridCell {
        PixelInImage superpixel;
        double SLIC_distance = pow(10, 18);
    };

private:
    using SuperPixels = std::vector<PixelInImage>;
    using ClusterGrid = std::vector<std::vector<ClusterGridCell>>;

    void InitializeSuperpixels();
    void InitializeClusterGrid();
    void NeighborhoodProcessing(const PixelInImage& superpixel);

    const Image& image_;
    int32_t number_of_clusters_;
    const double compactness_;
    double distance_between_sp_;
    double xy_coefficient_;
    int32_t width_;
    int32_t height_;

    SuperPixels super_pixels_;
    ClusterGrid cluster_grid_;
};