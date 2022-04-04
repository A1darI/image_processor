#pragma once

#include "image.h"
#include "filters/filter.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

class Parser {
public:
    Parser(int argc, const char* argv[]);
    void Parse();

    std::string GetFileToRead() const;
    std::string GetFileToWrite() const;
    std::vector<std::unique_ptr<Filter>>& GetFilters();

private:
    using Command = std::function<void()>;
    using CommandName = std::string;

    void Consume();
    void ParseCrop();
    void ParseGs();
    void ParseNeg();
    void ParseSharp();
    void ParseEdge();
    void ParseBlur();
    void ParseCrystallize();
    const int argc_;
    const char** argv_;
    int pos_ = 1;

    std::unordered_map<CommandName, Command> commands_;

    std::string file_to_read_;
    std::string file_to_write_;
    std::vector<std::unique_ptr<Filter>> filters_ = {};
};