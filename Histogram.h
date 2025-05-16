#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <map>
#include <vector>
#include <cstddef>
#include <limits>
#include <stdexcept>

class Adder{
public:
    virtual ~Adder() = default;

    virtual void add(double value) = 0;
};

class Histogram final : virtual Adder{
public:
    Histogram() = default;
    Histogram(const Histogram&)=default;
    Histogram(double min, double max, std::size_t bin_count);
    Histogram(const std::vector<double>& data, double min, double max, std::size_t bin_count);

    void add(double value) override;
    //void add(const std::vector<double>& data);

    [[nodiscard]] auto begin() const noexcept { return bins_.begin(); }
    [[nodiscard]] auto end() const noexcept { return bins_.end(); }
    [[nodiscard]] size_t size() const noexcept { return bins_.size(); }

    size_t& operator[](const size_t i) { return bins_[i]; };

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
    static bool eqwl(double a1, double a2) { return std::abs(a1 - a2) < 10e-6; };
    void addable(const Histogram &other) const { if (!eqwl(min_, other.min_) || !eqwl(max_, other.max_) || bins_.size() != other.bins_.size())
        throw std::logic_error("wrong parameters!");
    };
};

#endif // HISTOGRAM_H
