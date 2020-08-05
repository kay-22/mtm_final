#include <iostream>

#include <string>
#include <g_utility.h>

using std::string;
using std::cout;
using std::endl;

using graph::VertexName;

int main(int, char**) {
    VertexName vn1("abc");
    VertexName vn2(string("ab[]c"));
    VertexName vn3(string("ab[c"));
    VertexName vn4(string("ab][c"));
    VertexName vn5(string("[a;;b;c];["));
    VertexName vn6(string("[a;][;][a;;b;c][[];][]"));
    VertexName vn7(string("[a;;b;c][]"));
}
