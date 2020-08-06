#include "GraphTest.h"



using graph::Graph;
using graph::Vertex;
using graph::makeEdge;
using graph::GraphExsitingElementException;
using graph::GraphNoElementException;
using graph::GraphNameException;

using std::string;
using std::function;
using std::vector;
using std::cout;
using std::endl;

bool GraphTest::test_1() 
{
    Graph g1;
    g1.addVertex(Vertex("v1"));
    g1.addVertex(Vertex("v2"));
    g1.addEdge(makeEdge(Vertex("v1"), Vertex("v2")));

    cout << g1 << endl;

    try
    {
        g1.addEdge(makeEdge(Vertex("v1"), Vertex("v2")));
        return false;
    }
    catch(const GraphExsitingElementException& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        g1.addVertex(Vertex("v2"));
        return false;
    }
    catch(const GraphExsitingElementException& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        g1.containsEdge(makeEdge(Vertex("v1"), Vertex("V2")));
    }
    catch(const GraphNoElementException& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

bool GraphTest::test_2()
{
    try
    {
        Graph g("1g");
        return false;
    }
    catch(const GraphNameException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    Graph g1("abc");
    Graph g2("abb");
    Graph g3("aaa");
    Graph g4("zzz");
    Graph g5("z");
    return (g4 < g5) && (g4 < g1) && (g4 < g2) && (g4 < g3) &&
            (g5 < g3) && (g5 < g2) && (g5 < g1) &&
            (g1 < g2) && (g1 < g3) &&
            (g2 < g3);
}

bool GraphTest::test_3()
{
    Vertex v1("v1");
    Vertex v2("v2");
    Vertex v3("v3");

    Graph g1("g1");
    g1.addVertex(v1);
    g1.addVertex(v2);
    g1.addEdge(makeEdge(v1, v2));

    Graph g2;
    g2.addVertex(v1);
    g2.addVertex(v3);
    g2.addEdge(makeEdge(v1, v3));

    Graph g3("g3");
    g3 = g1 + g2;

    bool name_check_expected = string("g3") < string("unnamed");
    bool name_check = g3 < g2;

    if (name_check_expected != name_check) {
        return false;
    }

    if (!g3.containsVertex(v1) || !g3.containsVertex(v2) || !g3.containsVertex(v3)) {
        return false;
    }

    if (g3.containsEdge(makeEdge(v2, v3))) {
        return false;
    }

    if (!g3.containsEdge(makeEdge(v1, v2)) || !g3.containsEdge(makeEdge(v1, v3))) {
        return false;
    }

    return true;
}

void GraphTest::run_test(function<bool()> test, string test_name)
{
    if (!test())
    {
        cout << test_name << " FAILED." << endl;
        return;
    }
    cout << test_name << " SUCCEEDED." << endl;
}

void GraphTest::run_all_tests()
{
    vector<function<bool()>> tests{test_1, test_2, test_3};
    for (int i = 0; i < int(tests.size()); ++i)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Running test #" << i << "..." << endl;
        run_test(tests[i], "Test " + std::to_string(i));
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}