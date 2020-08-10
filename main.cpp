#include <iostream>
#include <fstream>
#include <string>

#include "g_calc/GraphCalculator.h"

using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using graph::Graph;
using graph::makeGraph;
using graph::VertexName;
using graph::Exception;
using graph::GraphCalculator;

static const int BATCH_MODE = 3;
static const int INTERACTIVE_MODE = 1;
static const int IN_FILE = 1;
static const int OUT_FILE = 2;

// void foomain()
// {
//     GraphTest::run_all_tests();

//     VertexName vn1("abc");
//     VertexName vn2(string("ab[]c"));

//     try {
//         VertexName vn3(string("ab[c"));
//     }
//     catch (const Exception& e) {
//         cout << e.what() << endl;
//     }

//     try {
//         VertexName vn4(string("ab][c"));
//     }
//     catch (const Exception& e) {
//         cout << e.what() << endl;
//     }

//     try {
//         VertexName vn5(string("[a;;b;c];["));
//     }
//     catch (const Exception& e) {
//         cout << e.what() << endl;
//     }
//        try {
//         VertexName vn8(string("[a;;b;c];[]"));
//     }
//     catch (const Exception& e) {
//         cout << e.what() << endl;
//     }
    
//     VertexName vn6(string("[a;][;][a;;b;c][[];][]"));
//     VertexName vn7(string("[a;;b;c][]"));

//     Graph ohoh = makeGraph("{a,b | <a,b>, <b, a>}", "gg");
//     cout << ohoh << endl;

//     string ohoh_l = ohoh.makeLiteral();
//     cout << ohoh_l << endl;
    
//     Graph ohohoh = makeGraph(ohoh_l, "ggg");
//     cout << ohohoh << endl;

//}

int main(int argc, char** argv) {
    //foomain();
    GraphCalculator gcalc;
    
    try{
        if (argc == BATCH_MODE){
        //if(true){
            ifstream input(argv[IN_FILE]);
            //ifstream input("g_test\\2.2&2.5\\batch\\t1in.txt");
            if (!input) {
                cerr << "Error: fatal error occured -- could not open input file" << endl;
                return 1;
            }

            ofstream output(argv[OUT_FILE]);
            //ofstream output("out.txt");
            if (!output) {
                cerr << "Error fatal error occured -- could not open output file" << endl;
                return 1;
            }

            gcalc.runBatch(input, output);

        }
        
        else if (argc == INTERACTIVE_MODE) {
            gcalc.run();
        }
        else {
            cerr << "Error: fatal error occured -- incorrect number of arguments" << endl;
            return 1;
        }
    }
    catch (...) {
        return 1;
    }

    return 0;
}
