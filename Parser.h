#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <istream>

#define part_size 1024

class Parser {
public:
    static std::vector<double> get_data(std::istream& stream);
    inline static bool finish = false;
};

#endif // PARSER_H