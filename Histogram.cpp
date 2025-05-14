#include "Histogram.h"
#include <cmath>
#include <stdexcept>

using namespace std;

Histogram::Histogram(double min, double max, size_t bin_count) : min_(min), max_(max) {
    if (isnormal(min) && isnormal(max) == false) {
        throw runtime_error("ERROR! wrong histogram parameters");
    }
    if (bin_count == 0 || max_ <= min_) {
        throw runtime_error("ERROR! wrong histogram parameters");
    }
    bin_size_ = (max_ - min_) / static_cast<int>(bin_count);
    bins_.resize(bin_count,0);
}

Histogram::Histogram(const vector<double>& data, double min, double max, size_t bin_count) : Histogram(min, max, bin_count) {
    add(data);
}

void Histogram::add(double value) {
    if (!isnormal(value)) {
        throw runtime_error("ERROR! trying add bad value to histogram");
    }
    int idx = static_cast<int>(floor((value - min_) / bin_size_));
    if (idx < 0) idx = 0;
    if (static_cast<size_t>(idx) >= bins_.size()) idx = static_cast<int>(bins_.size() - 1);
    bins_[static_cast<size_t>(idx)]++;
}

void Histogram::add(const vector<double>& data) {
    for (double v : data) {
        add(v);
    }
}

Histogram& Histogram::operator+=(const Histogram& other) {
    if (min_ != other.min_ || max_ != other.max_ || bins_.size() != other.bins_.size()) {
        throw runtime_error("addition logic error");
    }
    for (size_t i = 0; i < bins_.size(); i++) {
        bins_[i] += other.bins_[i];
    }
    return *this;
}

Histogram& Histogram::operator-=(const Histogram& other) {
    if (min_ != other.min_ || max_ != other.max_ || bins_.size() != other.bins_.size()) {
        throw runtime_error("subtraction logic error");
    }
    for (size_t i = 0; i < bins_.size(); i++) {
        bins_[i] = bins_[i] > other.bins_[i] ? bins_[i] - other.bins_[i] : 0;
    }
    return *this;
}

Histogram Histogram::operator+(const Histogram& other) const {
    Histogram result(*this);
    result += other;
    return result;
}

Histogram Histogram::operator-(const Histogram& other) const {
    Histogram result(*this);
    result -= other;
    return result;
}

bool Histogram::operator==(const Histogram& other) const {
    if (min_ == other.min_ && max_ == other.max_ && bins_.size() == other.bins_.size()) {
        return bins_ == other.bins_;
    } else return false;
}

bool Histogram::operator!=(const Histogram& other) const {
    return !(*this == other);
}
