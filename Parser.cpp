#include "Parser.h"
#include <vector>
#include <stdexcept>

std::vector<double> Parser::get_data(std::istream& stream) {
    if (!stream.good()) {
        throw std::runtime_error("ERROR! wrong stream");
    }
    double value;
    std::vector<double> data;
    while (stream >> value) {
        data.emplace_back(value);
    }
    if (data.empty()) {
        throw std::runtime_error("ERROR! no data");
    }
    return data;
}