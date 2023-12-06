#ifndef __SELF_TEST_H__
#define __SELF_TEST_H__

enum class result_t : unsigned int
{
    SUCCESS = 0,
    ERROR = 1
};

inline result_t operator|=(result_t& first, result_t second)
{   
    if (first != result_t::SUCCESS || second != result_t::SUCCESS) {
        first = result_t::ERROR;
    }

    return first;
}

result_t self_test();

#endif // __SELF_TEST_H__
