#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <map>
#include <vector>
#include <cstddef>
#include <stdexcept>

class Histogram {
public:
    Histogram() = default;
    Histogram(const Histogram&)=default;
    Histogram(double min, double max, std::size_t bin_count);
    Histogram(const std::vector<double>& data, double min, double max, std::size_t bin_count);

    void add(double value);
    void add(const std::vector<double>& data);

    auto begin() const noexcept { return bins_.begin(); }
    auto end() const noexcept { return bins_.end(); }
    auto at(const std::vector<size_t>::const_iterator it) noexcept(false) {return bins_.at(it - bins_.begin());}
    auto id(const std::vector<size_t>::const_iterator it) noexcept(false) {return static_cast<size_t>(it - bins_.begin());}

    Histogram& operator=(const Histogram& other) = default;
    Histogram& operator+=(const Histogram& other);
    Histogram& operator-=(const Histogram& other);

    Histogram operator+(const Histogram& other) const;
    Histogram operator-(const Histogram& other) const;

    bool operator==(const Histogram& other) const;
    bool operator!=(const Histogram& other) const;

private:
    double min_ = 0;
    double max_ = 0;
    double bin_size_ = 0;
    std::vector<std::size_t> bins_ = {};
};

#endif // HISTOGRAM_H
