#include <iostream>
#include "mnp.h"

void proces_errors(const std::string &error) {
    if (!error.empty()) {
        std::cerr << error;
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        proces_errors("Wrong input format! Should be [input file][output file][transform].");
    }

    const char *in = argv[1], *out = argv[2];
    mnp *simple_image_editor = new mnp();
    std::string error;
    error = simple_image_editor->read(in);
    proces_errors(error);

    switch (argv[3][0]) {
        case '0': {
            simple_image_editor->negative();
            break;
        }
        case '1': {
            simple_image_editor->horizontal();
            break;
        }
        case '2': {
            simple_image_editor->vertical();
            break;
        }
        case '3': {
            error = simple_image_editor->right();
            break;
        }
        case '4': {
            error = simple_image_editor->left();
            break;
        }
        default: {
            error = "Wrong input format! Transform should be int from [0, 4].";
        }
    }

    proces_errors(error);

    error = simple_image_editor->write(out);
    proces_errors(error);

    delete simple_image_editor;
    return 0;
}