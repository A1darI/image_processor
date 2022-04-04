#include "file_working_utilities.h"

int32_t file_handling::GetPadding(const Image &image) {
    return image.GetWidth() % 4;
}
