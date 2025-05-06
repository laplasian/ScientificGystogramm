#include "Parser.h"
#include "Gystogramm.h"
#include <iostream>
#include <fstream>

void print_hist(const Gystogramm& hist) {
    for (auto it = hist.begin(); it != hist.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "args error" << std::endl;
        return -1;
    }
    const char* input_fn = argv[1];
    double min = std::stod(argv[2]);
    double max = std::stod(argv[3]);
    size_t bins = static_cast<size_t>(std::stoul(argv[4]));

    try {
        std::ifstream in(input_fn);
        auto data = Parser::get_data(in);
        in.close();
        Gystogramm hist(data, min, max, bins);
        print_hist(hist);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
