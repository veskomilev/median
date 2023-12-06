#include "self_test.h"

#include "median_calculator.h"

#include <iostream>
#include <iomanip>
#include <string>

template<typename T>
result_t run_test(T result, T expectation, std::string test_name)
{
    std::cout << "Running " << test_name << "...";

    if (result != expectation) {
        std::cout << " error!\n"
            << "!> " << test_name << " failed:\n"
            << "!> test result is " << result << "\n"
            << "!> and expected result is " << expectation << std::endl;

        return result_t::ERROR;
    }

    std::cout << " success" << std::endl;

    return result_t::SUCCESS;
}

result_t self_test()
{
    result_t rc = result_t::SUCCESS;

    MedianCalculator<int> mc1(-5);
    int median = mc1.calculateMedian();
    rc |= run_test<int>(median, -5, "simple int test");


    rc |= run_test<int>(mc1.calculateMedian(), median, "consistency test");


    mc1.addToSample(6);
    mc1.addToSample(6);
    rc |= run_test<int>(mc1.calculateMedian(), 6, "new median test");


    MedianCalculator<int> mc2(6);
    mc2.addToSample(6);
    mc2.addToSample(-5);
    rc |= run_test<int>(mc1.calculateMedian(), mc2.calculateMedian(), "independent calculators test");


    MedianCalculator<float> mc3(-213.0f);
    mc3.addToSample(0.0f);
    mc3.addToSample(100.0f);
    mc3.addToSample(6547.044f);
    mc3.addToSample(432.0f);
    mc3.addToSample(1.0f);
    rc |= run_test<float>(mc3.calculateMedian(), 50.5f, "float median test");


    MedianCalculator<double> mc4(0.0);
    mc4.addToSample(5.0);
    mc4.addToSample(2.0);
    mc4.addToSample(2.0);
    mc4.addToSample(4.0);
    mc4.addToSample(3.0);
    mc4.addToSample(1.0);
    rc |= run_test<double>(mc4.calculateMedian(), 2.0, "double median test");

    return rc;
}
