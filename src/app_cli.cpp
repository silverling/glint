#include "app.h"

#include <getopt.h>

namespace App {

void App::parseArgs(const int argc, char *const *argv) {
    int opt;
    while ((opt = getopt(argc, argv, "f")) != -1) {
        switch (opt) {
        case 'f':
            // After -f, expect 1-N filenames until next option or end
            while (optind < argc && argv[optind][0] != '-') {
                std::string file = argv[optind];
                if (file.ends_with(".raw")) {
                    this->eventFiles.emplace_back(file);
                }
                optind++;
            }
            break;
        default:
            printf("Usage: %s [ -f <file> [<file> ...] ]\n", argv[0]);
            exit(1);
        }
    }
}

} // namespace App