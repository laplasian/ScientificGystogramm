#include "Parser.h"
#include "Histogram.h"
#include <iostream>
#include <fstream>
#include <string>

void print_hist(Histogram& hist) {
    std::cout << "histogram: " << std::endl;
    for (auto it = hist.begin(); it != hist.end(); ++it) {
        std::cout << hist.id(it) << " - " << hist.at(it) << std::endl;
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
        Histogram hist(min, max, bins);
        while (Parser::finish != true) {
            auto data = Parser::get_data(in);
            hist.add(data);
        }
        in.close();
        print_hist(hist);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
