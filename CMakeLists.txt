cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        image.cpp
        filters/crop.cpp filters/single_pixel_filter.cpp filters/matrix_filter.cpp filters/grayscale.cpp filters/negative.cpp filters/sharpening.cpp filters/edge_detection.cpp filters/gaussian_blur.cpp cmd_parser.cpp file_handling/reader.cpp file_handling/file_working_utilities.cpp file_handling/writer.cpp file_handling/exceptions.cpp filters/slic_crystallize.cpp filters/image_slic_clustering.cpp print_help.cpp)
