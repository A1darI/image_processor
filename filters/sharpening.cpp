#include "sharpening.h"

Sharpening::Sharpening() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}) {
}
