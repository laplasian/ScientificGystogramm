#include "Parser.h"
#include "Histogram.h"
#include <iostream>
#include <fstream>
#include <string>

void print_hist(Histogram& hist) {
    std::cout << "histogram: " << std::endl;
    for (int i = 0; i < hist.size(); i++) {
        std::cout << i << " - " << hist[i] << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "Error! Please input parameters in correct order: input_filename, min, max, bins_count" << std::endl;
        return -1;
    }
    const char* input_fn = argv[1];
    double min = std::stod(argv[2]);
    double max = std::stod(argv[3]);
    size_t bins = static_cast<size_t>(std::stoul(argv[4]));

    try {
        std::ifstream in(input_fn);
        Histogram hist(min, max, bins);
        auto p = Parser((Adder&)hist);
        p.get_data(in);
        in.close();
        print_hist(hist);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
