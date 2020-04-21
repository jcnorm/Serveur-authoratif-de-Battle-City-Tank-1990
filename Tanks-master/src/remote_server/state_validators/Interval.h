#ifndef INTERVAL_H
#define INTERVAL_H

template<class T>
class Interval{
    T min;
    T max;
public:
    Interval() {};
    Interval(const T minMax) : min(minMax), max(minMax){}
    Interval(const T minVal, const T maxVal) : min(minVal), max(maxVal) {}
    Interval(const Interval& interval) = delete;
    Interval& operator=(const Interval& interval) = delete;
    ~Interval() = default;

    [[nodiscard]] const bool IsValid(T val) const{
        return min <= val && val <= max;
    }

    [[nodiscard]] const T GetMin() const{
        return min;
    }

    void SetValues(const T minVal, const T maxVal){
        min = minVal;
        max = maxVal;
    }

    [[nodiscard]] const T GetMax() const{
        return max;
    }

    [[nodiscard]] const T GetClosestValue(T val) const{
        return (val > max) ? max : min;
    }
};

#endif