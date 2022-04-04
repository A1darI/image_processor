#include "image_slic_clustering.h"
#include <unordered_map>
#include <iostream>

template <typename T>
T Square(T number) {
    return number * number;
}

double RGBDistance(const ImageClustering::PixelInImage& pixel1, const ImageClustering::PixelInImage& pixel2) {
    return sqrt(Square(pixel1.pixel.red - pixel2.pixel.red) + Square(pixel1.pixel.blue - pixel2.pixel.blue) +
                Square(pixel1.pixel.green - pixel2.pixel.green));
}

double XYDistance(const ImageClustering::PixelInImage& pixel1, const ImageClustering::PixelInImage& pixel2) {
    return sqrt(Square(pixel1.y - pixel2.y) + Square(pixel1.x - pixel2.x));
}

double SLICDistance(const ImageClustering::PixelInImage& pixel1, const ImageClustering::PixelInImage& pixel2,
                    double xy_coefficient) {
    return RGBDistance(pixel1, pixel2) + xy_coefficient * XYDistance(pixel1, pixel2);
}

ImageClustering::ImageClustering(const Image& image, int32_t number_of_clusters, double compactness)
    : image_(image), number_of_clusters_(number_of_clusters), compactness_(compactness) {
    InitializeSuperpixels();
}
void ImageClustering::InitializeSuperpixels() {
    double width = image_.GetWidth();
    double height = image_.GetHeight();
    width_ = width;
    height_ = height;
    double image_size = width * height;
    double sp_size = image_size / number_of_clusters_;
    double sp_distance = sqrt(sp_size);
    distance_between_sp_ = sp_distance;
    xy_coefficient_ = compactness_ / distance_between_sp_;
    int32_t offset = sp_distance / 2;
    double sp_grid_size = sqrt(number_of_clusters_);
    int32_t sp_h_step = height / sp_grid_size + 1;
    int32_t sp_w_step = width / sp_grid_size + 1;
    int32_t current_num_of_clusters = 0;
    super_pixels_.reserve(number_of_clusters_);
    for (int32_t y = offset; y < height_; y += sp_h_step) {
        for (int32_t x = offset; x < width_; x += sp_w_step) {
            if (current_num_of_clusters == number_of_clusters_) {
                continue;
            }
            super_pixels_.push_back({image_.GetPixel(x, y), y, x});
            ++current_num_of_clusters;
        }
    }
    number_of_clusters_ = current_num_of_clusters;
    super_pixels_.shrink_to_fit();
}
void ImageClustering::InitializeClusterGrid() {
    cluster_grid_ = std::vector<std::vector<ClusterGridCell>>(height_, std::vector<ClusterGridCell>(width_));
}
void ImageClustering::ReinitializeClusterGrid() {
    InitializeClusterGrid();
    for (size_t i = 0; i < super_pixels_.size(); ++i) {
        NeighborhoodProcessing(super_pixels_[i]);
    }
}
void ImageClustering::NeighborhoodProcessing(const PixelInImage& superpixel) {
    int32_t center_x = superpixel.x;
    int32_t center_y = superpixel.y;
    int32_t radius = distance_between_sp_;
    int32_t up_y_limit = std::min(height_ - 1, center_y + radius);
    int32_t down_y_limit = std::max(0, center_y - radius);
    int32_t left_x_limit = std::max(0, center_x - radius);
    int32_t right_x_limit = std::min(width_ - 1, center_x + radius);
    for (int32_t y = down_y_limit; y <= up_y_limit; ++y) {
        for (int32_t x = left_x_limit; x <= right_x_limit; ++x) {
            PixelInImage pixel = {image_.GetPixel(x, y), y, x};
            double slic_distance = SLICDistance(superpixel, pixel, xy_coefficient_);
            if (cluster_grid_[y][x].SLIC_distance > slic_distance) {
                cluster_grid_[y][x] = {superpixel, slic_distance};
            }
        }
    }
}

struct PixelInImageHash {
    size_t operator()(const ImageClustering::PixelInImage& pixel) const {
        return std::hash<int32_t>{}(pixel.x * 1001 + pixel.y);
    }
};

double ImageClustering::ReinitializeSuperpixels() {

    struct PixelSum {
        int32_t red = 0;
        int32_t green = 0;
        int32_t blue = 0;
        int32_t y = 0;
        int32_t x = 0;
        size_t number_of_pixels = 0;
    };

    std::unordered_map<PixelInImage, PixelSum, PixelInImageHash> superpixels_har;
    for (int32_t y = 0; y < height_; ++y) {
        for (int32_t x = 0; x < width_; ++x) {
            PixelInImage pixel_in_image = {image_.GetPixel(x, y), y, x};
            superpixels_har[cluster_grid_[y][x].superpixel].number_of_pixels += 1;
            auto pair_ptr = superpixels_har.find(cluster_grid_[y][x].superpixel);
            pair_ptr->second.y += pixel_in_image.y;
            pair_ptr->second.x += pixel_in_image.x;
            pair_ptr->second.red += pixel_in_image.pixel.red;
            pair_ptr->second.green += pixel_in_image.pixel.green;
            pair_ptr->second.blue += pixel_in_image.pixel.blue;
        }
    }

    for (auto& [superpixel, pixel_sum] : superpixels_har) {
        size_t number_of_pixels = pixel_sum.number_of_pixels;
        pixel_sum.blue /= number_of_pixels;
        pixel_sum.green /= number_of_pixels;
        pixel_sum.red /= number_of_pixels;
        pixel_sum.x /= number_of_pixels;
        pixel_sum.y /= number_of_pixels;
    }
    double error = 0;
    for (size_t i = 0; i < super_pixels_.size(); ++i) {
        auto new_pixel_ptr = superpixels_har.find(super_pixels_[i]);
        Pixel new_pixel;
        new_pixel.red = new_pixel_ptr->second.red;
        new_pixel.green = new_pixel_ptr->second.green;
        new_pixel.blue = new_pixel_ptr->second.blue;
        PixelInImage new_sp = {new_pixel, new_pixel_ptr->second.y, new_pixel_ptr->second.x};
        error += SLICDistance(new_sp, super_pixels_[i], xy_coefficient_);
        super_pixels_[i] = new_sp;
    }
    return error / number_of_clusters_;
}
Image ImageClustering::GetImage(bool have_edges) const {
    Image result_image(height_, width_);
    for (int32_t y = 0; y < height_; ++y) {
        for (int32_t x = 0; x < width_; ++x) {
            if (have_edges && y > 0 && x > 0 &&
                !(cluster_grid_[y][x].superpixel == cluster_grid_[y - 1][x - 1].superpixel)) {
                result_image.SetPixel(x, y, {0, 0, 0});
            } else {
                Pixel pixel = cluster_grid_[y][x].superpixel.pixel;
                result_image.SetPixel(x, y, pixel);
            }
        }
    }
    return result_image;
}
bool ImageClustering::PixelInImage::operator==(const ImageClustering::PixelInImage& pixel_in_image) const {
    return (pixel.red == pixel_in_image.pixel.red) && (pixel.blue == pixel_in_image.pixel.blue) &&
           (pixel.green == pixel_in_image.pixel.green) && (y == pixel_in_image.y) && (x == pixel_in_image.x);
}
