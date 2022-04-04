#include "cmd_parser.h"
#include "filters/all_filters.h"
#include <iostream>

Parser::Parser(int argc, const char* argv[]) : argc_(argc), argv_(argv) {
    commands_["-crop"] = [&]() { ParseCrop(); };
    commands_["-gs"] = [&]() { ParseGs(); };
    commands_["-neg"] = [&]() { ParseNeg(); };
    commands_["-sharp"] = [&]() { ParseSharp(); };
    commands_["-edge"] = [&]() { ParseEdge(); };
    commands_["-blur"] = [&]() { ParseBlur(); };
    commands_["-crystallize"] = [&]() { ParseCrystallize(); };
}
void Parser::Parse() {
    if (argc_ < 3) {
        throw std::invalid_argument("usage: <file1> <file2> ...");
    }
    file_to_read_ = argv_[1];
    file_to_write_ = argv_[2];
    pos_ += 2;
    while (pos_ < argc_) {
        Consume();
    }
}
void Parser::ParseCrop() {
    pos_ += 2;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -crop <width> <height>");
    }
    int32_t width = 0;
    int32_t height = 0;
    try {
        width = std::stoi(argv_[pos_ - 1]);
        height = std::stoi(argv_[pos_]);
        if (width <= 0 || height <= 0) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Crop filter arguments: width, height must be positive integer");
    }
    filters_.push_back(std::make_unique<Crop>(height, width));
}

void Parser::ParseGs() {
    filters_.push_back(std::make_unique<GrayScale>());
}
void Parser::ParseNeg() {
    filters_.push_back(std::make_unique<Negative>());
}
void Parser::ParseSharp() {
    filters_.push_back(std::make_unique<Sharpening>());
}
void Parser::ParseEdge() {
    ++pos_;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -edge <threshold>");
    }
    double threshold = 0;
    try {
        threshold = std::stod(argv_[pos_]);
        if (threshold < 0 || 1 < threshold) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Edge filter arguments: threshold must be real from 0 to 1");
    }
    filters_.push_back(std::make_unique<EdgeDetection>(threshold));
}
void Parser::ParseBlur() {
    ++pos_;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -blur <sigma>");
    }
    double sigma;
    try {
        sigma = std::stod(argv_[pos_]);
    } catch (const std::exception& e) {
        throw std::invalid_argument("Blur filter arguments: sigma must be real");
    }
    filters_.push_back(std::make_unique<GaussianBlur>(sigma));
}

void Parser::ParseCrystallize() {
    pos_ += 2;
    if (pos_ > argc_) {
        throw std::out_of_range("usage: -crystallize <number of clusters> <compactness>");
    }
    int32_t number_of_clusters = 0;
    double compactness = 0;
    try {
        number_of_clusters = std::stoi(argv_[pos_ - 1]);
        compactness = std::stod(argv_[pos_]);
        if (number_of_clusters <= 0 || compactness <= 0) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument(
            "Crystallize filter arguments: number_of_clusters must be positive integer, compactness must be positive "
            "real");
    }
    filters_.push_back(std::make_unique<Crystallize>(number_of_clusters, compactness));
}

void Parser::Consume() {
    CommandName command_name = argv_[pos_];
    auto it = commands_.find(command_name);
    if (it != commands_.end()) {
        it->second();
    } else {
        throw std::invalid_argument("need filter name, get " + std::string(argv_[pos_]));
    }
    ++pos_;
}

std::string Parser::GetFileToRead() const {
    return file_to_read_;
}
std::string Parser::GetFileToWrite() const {
    return file_to_write_;
}
std::vector<std::unique_ptr<Filter>>& Parser::GetFilters() {
    return filters_;
}
