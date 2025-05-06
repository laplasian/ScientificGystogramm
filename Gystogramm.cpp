#include "Gystogramm.h"
#include <cmath>
#include <stdexcept>

using namespace std;

Gystogramm::Gystogramm(double min, double max, size_t bin_count) : min_(min), max_(max), bin_count_(bin_count) {
    if (bin_count_ == 0 || max_ <= min_) {
        throw runtime_error("ERROR! wrong histogram parameters");
    }
    bin_size_ = (max_ - min_) / bin_count_;
    init_bins();
}

Gystogramm::Gystogramm(const vector<double>& data, double min, double max, size_t bin_count) : Gystogramm(min, max, bin_count) {
    add(data);
}

void Gystogramm::init_bins() {
    bins_.clear();
    for (size_t i = 0; i < bin_count_; ++i) {
        bins_[i] = 0;
    }
}

void Gystogramm::add(double value) {
    int idx = static_cast<int>(floor((value - min_) / bin_size_));
    if (idx < 0) idx = 0;
    if (static_cast<size_t>(idx) >= bin_count_) idx = static_cast<int>(bin_count_ - 1);
    bins_[static_cast<size_t>(idx)]++;
}

void Gystogramm::add(const vector<double>& data) {
    for (double v : data) {
        add(v);
    }
}

Gystogramm& Gystogramm::operator+=(const Gystogramm& other) {
    if (min_ != other.min_ || max_ != other.max_ || bin_count_ != other.bin_count_) {
        throw runtime_error("ERROR! different parameters");
    }
    for (auto& kv : bins_) {
        kv.second += other.bins_.at(kv.first);
    }
    return *this;
}

Gystogramm& Gystogramm::operator-=(const Gystogramm& other) {
    if (min_ != other.min_ || max_ != other.max_ || bin_count_ != other.bin_count_) {
        throw runtime_error("ERROR! different parameters");
    }
    for (auto& v : bins_) {
        size_t other_count = other.bins_.at(v.first);
        if (v.second < other_count) {
            throw runtime_error("ERROR! negative count");
        }
        v.second -= other_count;
    }
    return *this;
}

Gystogramm Gystogramm::operator+(const Gystogramm& other) const {
    Gystogramm result(*this);
    result += other;
    return result;
}

Gystogramm Gystogramm::operator-(const Gystogramm& other) const {
    Gystogramm result(*this);
    result -= other;
    return result;
}

bool Gystogramm::operator==(const Gystogramm& other) const {
    if (min_ == other.min_ && max_ == other.max_ && bin_count_ == other.bin_count_) {
        return bins_ == other.bins_;
    } else throw runtime_error("ERROR! different parameters");
}

bool Gystogramm::operator!=(const Gystogramm& other) const {
    return !(*this == other);
}
