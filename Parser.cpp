#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<double> Parser::get_data(std::istream& stream) {
    if (!stream.good()) {
        throw std::runtime_error("ERROR! wrong stream");
    }
    double value;
    std::vector<double> data;
    int count = 0;
    while (count < part_size && stream >> value) {
        data.emplace_back(value);
        count++;
    }
    if (data.empty()) {
        throw std::runtime_error("ERROR! no data");
    }

    static int c = 1;
    if (count == part_size) {
        finish = false;
        std::cout << "parser red " << c << " part" << std::endl;
        c++;
    } else {
        std::cout << "reading file is completed" << std::endl;
        c = 1;
        finish = true;
    }

    return data;
}
