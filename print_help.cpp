#include "print_help.h"
#include <iostream>

void help::PrintHelp() {
    std::cout << "Usage:\timage_processor INPUT_FILE OUTPUT_FILE [-FILTER1 PARAM1 ...] [-FILTER2 PARAM1 ...]"
              << std::endl;
    std::cout << std::endl;

    std::cout << "Apply several filters to bpm image" << std::endl;
    std::cout << std::endl;

    std::cout << "Filters:" << std::endl;
    std::cout << "  -crop WIDTH(positive integer) HEIGHT(positive integer)    Crop image" << std::endl;
    std::cout << "  -gs    Apply grayscale" << std::endl;
    std::cout << "  -neg    Apply negative" << std::endl;
    std::cout << "  -sharp    Apply sharpening" << std::endl;
    std::cout << "  -edge THRESHOLD(real on [0, 1])    Apply edge detection" << std::endl;
    std::cout << "  -blur SIGMA(real)    Apply gaussian blur" << std::endl;
    std::cout << "  -crystallize NUMBER_OF_CLUSTERS(positive integer) COMPACTNESS(positive real)    Apply crystallize"
              << std::endl;
}