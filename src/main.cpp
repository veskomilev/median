#include <cstring>
#include <iostream>
#include <iomanip>

#include "self_test.h"

#include "median_calculator.h"

void print_usage(std::string executable_name)
{
    std::cout << "Usage:\n" << std::left
        << "  " << executable_name << std::setw(28) << " -h"
        << "print this menu and exit\n"
        << "  " << executable_name << std::setw(28) << " -t"
        << "run self tests\n"
        << "  " << executable_name << std::setw(28) << " -i <list of integers>"
        << "calculate median of integers\n"
        << "  " << executable_name << std::setw(28) << " -f <list of floats>"
        << "calculate median of floating point numbers\n"
        << "  " << executable_name << std::setw(28) << " -d <list of doubles>"
        << "calculate median of double precision floating point numbers"
        << std::endl;
}

void run_self_tests()
{
    result_t rc = self_test();

    if (rc == result_t::SUCCESS) {
        std::cout << ">> All tests were successful" << std::endl;
    } else {
        std::cout << ">> Tests failed" << std::endl;
    }
}

// stoi, stof and stod have different signatures, so wrap them
int convert_int(std::string input)
{
    return stoi(input);
}

float convert_float(std::string input)
{
    return stof(input);
}

double convert_double(std::string input)
{
    return stod(input);
}

template<typename T>
result_t convert_an_argument(T* result, std::string input, T (*conversion_function)(std::string))
{
    if (result == nullptr) {
        std::cout << "Result parameter is nullptr!" << std::endl;
        return result_t::ERROR;
    }

    try
    {
        *result = conversion_function(input);
        return result_t::SUCCESS;
    }
    catch(...)
    {
        std::cout << "Invalid input argument: '" << input << "'" << std::endl;
        return result_t::ERROR;
    }
}

template<typename T>
result_t handle_input_for_median(T* median, int argc, char* argv[], T (*conversion_function)(std::string))
{
    if (median == nullptr) {
        std::cout << "Result parameter is nullptr!" << std::endl;
        return result_t::ERROR;
    }

    if (argc < 3) {
        std::cout << "At least one more argument is expected" << std::endl;
        print_usage(std::string(argv[0]));
        return result_t::ERROR;
    }

    result_t rc;
    T initial_element;

    rc = convert_an_argument(&initial_element, argv[2], conversion_function);
    if (rc != result_t::SUCCESS) {
        return rc;
    }

    MedianCalculator<T> calculator(initial_element);

    for (int i = 3; i < argc; i++) {
        T new_element;

        rc = convert_an_argument(&new_element, argv[i], conversion_function);
        if (rc != result_t::SUCCESS) {
            return rc;
        }

        calculator.addToSample(new_element);
    }

    *median = calculator.calculateMedian();

    return result_t::SUCCESS;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "At least one argument is expected" << std::endl;
        print_usage(std::string(argv[0]));
        return 1;
    }

    if (!strcmp(argv[1], "-h")) {

        print_usage(std::string(argv[0]));

    } else if (!strcmp(argv[1], "-t")) {

        run_self_tests();

    } else if (!strcmp(argv[1], "-i")) {

        int median;
        result_t rc = handle_input_for_median<int>(&median, argc, argv, convert_int);

        if (rc == result_t::SUCCESS) {
            std::cout << "integer median of input is " << median << std::endl;
        }

    } else if (!strcmp(argv[1], "-f")) {

        float median;
        result_t rc = handle_input_for_median<float>(&median, argc, argv, convert_float);

        if (rc == result_t::SUCCESS) {
            std::cout << "float median of input is " << std::setprecision(6) << median << std::endl;
        }

    } else if (!strcmp(argv[1], "-d")) {

        double median;
        result_t rc = handle_input_for_median<double>(&median, argc, argv, convert_double);

        if (rc == result_t::SUCCESS) {
            std::cout << "double median of input is " << std::setprecision(15) << median << std::endl;
        }

    } else {

        std::cout << "Unrecognised argument: " << argv[1] << std::endl;
        print_usage(std::string(argv[0]));
        return 1;

    }

    return 0;
}
