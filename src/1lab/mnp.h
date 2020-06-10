#ifndef COMPUTER_GRAPHICS_MNP_H
#define COMPUTER_GRAPHICS_MNP_H


#include <string>
#include <fstream>
#include <cstring>

typedef unsigned char uchar;

class mnp {
public:
    std::string read(const char *input_file);

    std::string write(const char *output_file);

    bool empty() const;

    void clear() {
        is_empty = true;
        delete []arr;
        input.close();
        output.close();
    }

    void negative();

    std::string right();

    std::string left();

    void horizontal();

    void vertical();

    ~mnp() {
        clear();
    }
private:
    int size_x, size_y, depth, arr_size, arr_memory_size;
    uchar *arr;
    char file_type[2];
    bool is_empty = true;

    std::ifstream input;
    std::ofstream output;
};


#endif //COMPUTER_GRAPHICS_MNP_H
