#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <istream>
#include <stdexcept>

class Parser {
public:
    static std::vector<double> get_data(std::istream& stream);
};

#endif // PARSER_H