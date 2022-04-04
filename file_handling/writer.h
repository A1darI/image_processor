#pragma once
#include "file_working_utilities.h"
#include <string>

namespace file_handling {
void Write(const Image& image, const std::string& file);
int32_t GetSize(const Image &image);
}