#include <iostream>
#include "mnp.h"

std::string mnp::read(const char *input_file) {
    input.open(input_file, std::ios::binary);

    if (!input.is_open()) {
        clear();
        return "Can`t open input file for reading!";
    }

    input >> file_type >> size_x >> size_y >> depth;

    if (strcmp(file_type, "P5") != 0 && strcmp(file_type, "P6") != 0) {
        clear();
        return "Wrong input file format. Should be P5 or P6!";
    }

    arr_size = size_x * size_y;
    arr_memory_size = (strcmp(file_type, "P6") == 0 ? 3 : 1) * arr_size;

    try {
        arr = new uchar[arr_memory_size];
    } catch (std::bad_alloc &e) {
        clear();
        return "bad_alloc during creating array for image!";
    }

    input.get();
    input.read(reinterpret_cast<char *>(arr), arr_memory_size);

    if (input.gcount() != arr_memory_size) {
        clear();
        return "wrong image file size!";
    }

    input.close();

    is_empty = false;
    return "";
}

std::string mnp::write(const char *output_file) {
    output.open(output_file, std::ios::binary);

    if (!output.is_open()) {
        return "Can`t open output file for writting!";
    }

    output << file_type << std::endl << size_x << ' ' << size_y << std::endl << depth << std::endl;
    output.write(reinterpret_cast<const char *>(arr), arr_memory_size);
    output.close();
    return "";
}

bool mnp::empty() const {
    return is_empty;
}

void mnp::negative() {
    for (int i = 0; i < arr_size; i++) {
        arr[i] = depth - arr[i];
    }
}

std::string mnp::right() {
    uchar *tmp_arr = nullptr;

    try {
        tmp_arr = new uchar[arr_size];
    } catch (std::bad_alloc &e) {
        return "Can`t create temporary array for right turn!";
    }

    int ptr = 0;

    if (file_type[1] == '6') {
        for (int k = 0; k < 3; k++) {
            ptr = 0;
            for (int x = 0; x < size_x; x++) {
                for (int y = 0; y < size_y; y++) {
                    tmp_arr[k + 3 * ptr] = arr[k + 3 * (x + (size_y - y - 1) * size_x)];
                    ptr++;
                }
            }
        }
    } else {
        for (int x = 0; x < size_x; x++) {
            for (int y = 0; y < size_y; y++) {
                tmp_arr[ptr] = arr[x + (size_y - y - 1) * size_x];
                ptr++;
            }
        }
    }

    std::memcpy(arr, tmp_arr, arr_size);
    delete[] tmp_arr;
    std::swap(size_x, size_y);
    return "";
}

std::string mnp::left() {
    uchar *tmp_arr = nullptr;

    try {
        tmp_arr = new uchar[arr_size];
    } catch (std::bad_alloc &e) {
        return "Can`t create temporary array for left turn!";
    }

    int ptr = 0;

    if (file_type[1] == '6') {
        for (int k = 0; k < 3; k++) {
            ptr = 0;
            for (int x = 0; x < size_x; x++) {
                for (int y = 0; y < size_y; y++) {
                    tmp_arr[k + 3 * ptr] = arr[k + 3 * ((size_x - x - 1) + y * size_x)];
                    ptr++;
                }
            }
        }
    } else {
        for (int x = 0; x < size_x; x++) {
            for (int y = 0; y < size_y; y++) {
                tmp_arr[ptr] = arr[(size_x - x - 1) + y * size_x];
                ptr++;
            }
        }
    }

    std::memcpy(arr, tmp_arr, arr_size);
    delete[] tmp_arr;
    std::swap(size_x, size_y);
    return "";
}

void mnp::horizontal() {
    int ptr1, ptr2, tmp, pixel_size = (file_type[1] == '6' ? 3 : 1);
    for (int shift = 0; shift < pixel_size; shift++) {
        for (int y = 0; y < size_y; y++) {
            tmp = y * size_x;
            ptr1 = shift + pixel_size * tmp, ptr2 = shift + pixel_size * (size_x - 1 + tmp);
            for (int x = 0; x < size_x / 2; x++) {
                ptr1 += pixel_size, ptr2 -= pixel_size;
                std::swap(arr[ptr1], arr[ptr2]);
            }
        }
    }
}

void mnp::vertical() {
    int ptr1, ptr2, tmp, pixel_size = (file_type[1] == '6' ? 3 : 1);

    for (int shift = 0; shift < pixel_size; shift++) {
        for (int y = 0; y < size_y / 2; y++) {
            tmp = y * size_x;
            ptr1 = shift + pixel_size * tmp, ptr2 = shift + pixel_size * ((size_y - 1) * size_x - tmp);
            for (int x = 0; x < size_x; x++) {
                std::swap(arr[ptr1], arr[ptr2]);
                ptr1 += pixel_size, ptr2 += pixel_size;
            }
        }
    }
}


