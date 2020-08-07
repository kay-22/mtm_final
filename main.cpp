#include <iostream>
#include <string>

#include <g_utility.h>
#include <g_test.h>
#include <g_except.h>

using std::string;
using std::cout;
using std::endl;
using graph::VertexName;
using graph::Exception;

#include <functional>
using std::reference_wrapper;

class A
{
public:
    virtual void hi() = 0;
    virtual ~A() = default;
};

class B : public A 
{
    virtual void hi() override { cout << "hiB" << endl;}
};

class C : public A 
{
    virtual void hi() override { cout << "hiC" << endl;}
};

int main(int, char**) {
    GraphTest::run_all_tests();

    VertexName vn1("abc");
    VertexName vn2(string("ab[]c"));

    try {
        VertexName vn3(string("ab[c"));
    }
    catch (const Exception& e) {
        cout << e.what() << endl;
    }

    try {
        VertexName vn4(string("ab][c"));
    }
    catch (const Exception& e) {
        cout << e.what() << endl;
    }

    try {
        VertexName vn5(string("[a;;b;c];["));
    }
    catch (const Exception& e) {
        cout << e.what() << endl;
    }
       try {
        VertexName vn8(string("[a;;b;c];[]"));
    }
    catch (const Exception& e) {
        cout << e.what() << endl;
    }
    
    VertexName vn6(string("[a;][;][a;;b;c][[];][]"));
    VertexName vn7(string("[a;;b;c][]"));

}
