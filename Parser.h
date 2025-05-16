#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include "Histogram.h"

class Parser {
public:
    explicit Parser(Adder & obj): obj_(obj) {};
    void get_data(std::istream& stream) const;
private:
    Adder & obj_;
};

#endif // PARSER_H