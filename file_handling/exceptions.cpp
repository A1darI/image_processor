#include "exceptions.h"

FileOpenFailedException::FileOpenFailedException(const std::string& path) : message_("failed to open file: " + path) {
}
const char* FileOpenFailedException::what() const noexcept {
    return message_.c_str();
}