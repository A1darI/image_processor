#include "cmd_parser.h"
#include "file_handling/reader.h"
#include "file_handling/writer.h"
#include "print_help.h"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        help::PrintHelp();
        return 1;
    }
    Parser parser(argc, argv);
    parser.Parse();
    std::string file_to_read = parser.GetFileToRead();
    std::string file_to_write = parser.GetFileToWrite();
    Image image = file_handling::Read(file_to_read);
    std::vector<std::unique_ptr<Filter>>& filters = parser.GetFilters();
    for (size_t i = 0; i < filters.size(); ++i) {
        image = filters[i]->Apply(image);
    }
    file_handling::Write(image, file_to_write);
    return 0;
}
