#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H

#include <iostream>
#include <functional>
#include <vector>

#include <graph.h>
#include <g_except.h>

namespace GraphTest
{
    bool test_1();
    bool test_2();
    bool test_3();
    void run_test(std::function<bool()> test, std::string test_name);
    void run_all_tests();
} // namespace GraphTest


#endif // GRAPH_TEST_H
