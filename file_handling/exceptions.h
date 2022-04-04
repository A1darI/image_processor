#pragma once
#include <exception>
#include <string>

class FileOpenFailedException : public std::exception {
public:
    FileOpenFailedException(const std::string& path);
    const char* what() const noexcept override;

private:
    std::string message_;
};