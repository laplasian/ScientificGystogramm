#ifndef GYSTOGRAMM_H
#define GYSTOGRAMM_H

#include <map>
#include <vector>
#include <cstddef>
#include <stdexcept>

class Gystogramm {
public:
    Gystogramm() = default;
    Gystogramm(const Gystogramm&)=default;
    Gystogramm(double min, double max, std::size_t bin_count);
    Gystogramm(const std::vector<double>& data, double min, double max, std::size_t bin_count);

    void add(double value);
    void add(const std::vector<double>& data);

    auto begin() const noexcept { return bins_.begin(); }
    auto end() const noexcept { return bins_.end(); }

    Gystogramm& operator=(const Gystogramm& other) = default;
    Gystogramm& operator+=(const Gystogramm& other);
    Gystogramm& operator-=(const Gystogramm& other);

    Gystogramm operator+(const Gystogramm& other) const;
    Gystogramm operator-(const Gystogramm& other) const;

    bool operator==(const Gystogramm& other) const;
    bool operator!=(const Gystogramm& other) const;

private:
    double min_;
    double max_;
    std::size_t bin_count_;
    double bin_size_;
    std::map<std::size_t, std::size_t> bins_;

    void init_bins();
};

#endif // GYSTOGRAMM_H
