#ifndef INTERVAL_H
#define INTERVAL_H

template<class T>
class Interval{
    T min;
    T max;
public:
    Interval() = delete;
    Interval(const T minMax) : min(minMax), max(minMax){}
    Interval(const T minVal, const T maxVal) : min(minVal), max(maxVal) {}
    Interval(const Interval&) = delete;
    Interval& operator=(const Interval&) = delete;
    ~Interval() = default;

    [[nodiscard]] const bool IsValid(T val) const{
        return min <= val && val <= max;
    }
};

#endif