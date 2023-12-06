#ifndef __MEDIAN_CALCULATOR_H__
#error This file should be included by and only by median_calculator.h
#endif

#ifndef __MEDIAN_CALCULATOR_IMPLEMENTATION_H__
#define __MEDIAN_CALCULATOR_IMPLEMENTATION_H__


template <class element_t>
MedianCalculator<element_t>::MedianCalculator(element_t initial_element)
{
    sample_ = { initial_element };
    median_ = initial_element;
    has_been_calculated_ = true;
}

template <class element_t>
MedianCalculator<element_t>::~MedianCalculator()
{
}

template <class element_t>
void MedianCalculator<element_t>::addToSample(element_t new_element)
{
    has_been_calculated_ = false;
    sample_.push_back(new_element);
}

template <class element_t>
element_t MedianCalculator<element_t>::calculateMedian()
{
    if (has_been_calculated_) {
        return median_;
    }

    size_t sample_size = sample_.size();
    std::sort(sample_.begin(), sample_.end());

    if (sample_size % 2 == 1) {
        median_ = sample_[sample_size / 2];
    } else {
        element_t lower_element = sample_[sample_size / 2 - 1];
        element_t upper_element = sample_[sample_size / 2];
        median_ = (lower_element + upper_element) / 2;
    }

    has_been_calculated_ = true;

    return median_;
}

#endif // __MEDIAN_CALCULATOR_IMPLEMENTATION_H__
