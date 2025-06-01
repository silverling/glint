#include "app.h"

#include <iostream>

int main(const int argc, char **argv) {
    App::App app(argc, argv);

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}