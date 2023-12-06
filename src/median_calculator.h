#ifndef __MEDIAN_CALCULATOR_H__
#define __MEDIAN_CALCULATOR_H__

#include <algorithm>
#include <vector>

template <class element_t>
class MedianCalculator
{
public:
    explicit MedianCalculator(element_t initial_element);

    ~MedianCalculator();

    void addToSample(element_t new_element);

    element_t calculateMedian();
private:
    // disable copy and copy-by-assignment ctors
    MedianCalculator(const MedianCalculator&) = delete;
    MedianCalculator& operator=(const MedianCalculator&) = delete;

    std::vector<element_t> sample_;

    bool has_been_calculated_;

    element_t median_;
};

// a dirty trick to keep a template class definition and implementation in separate files
#include "median_calculator_implementation.h"

#endif // __MEDIAN_CALCULATOR_H__
