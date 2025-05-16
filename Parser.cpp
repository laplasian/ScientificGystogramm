#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

void Parser::get_data(std::istream& stream) const {
    if (!stream.good()) {
        throw std::runtime_error("ERROR! wrong stream");
    }
    double value;
    while (stream >> value) {
        obj_.add(value);
    }
}
