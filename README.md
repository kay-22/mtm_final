# gcalc
My final project for Intro to Sys. Programming at Technion university. This project was given as an experimental evaluation method instead of the traditional final exam, which was cancelled because of COVID-19. The [final code](archive/original_final.zip) was submitted on August 10th 2020. Graded 88/100.

This project implements a command-line graph (graph theory) calculator. User can assign graphs and manipulate them with various operators shuch as intersection, union, difference, product, and complement.
## Features
* can assign multiple graphs
* print a graph
* interactive mode -- make calculations on the go
* batch mode -- provide an input of instructions to be calculated
* save/load graphs on your machine
* python interface:
``` python
 import graph as gw
 g1 = gw.create()
 g1 = gw.addVertex(g1, 'a')
 g1 = gw.addVertex(g1, 'b')
 gw.disp(gw.addEdge(g1, 'a', 'b'))
 gw.destroy(g1)
```
## How to use
To create the executable run make. To use interactive mode, run the executable without arguments. You can then make calculations such as:
``` 
Gcalc> G1={x1,x2,x3,x4|<x4,x1>, <x3,x4>,<x2,x3>,<x1,x2>}
Gcalc> G2 = { x1,y1 | <x1,y1> }
Gcalc> H = G1 + G2
Gcalc> print(H)
x1
x2
x3
x4
y1
$
x1 x2
x1 y1
x2 x3
x3 x4
x4 x1
Gcalc> who
G1
G2
H
Gcalc> reset
Gcalc> print(H)
Error: Undefined variable 'H'
Gcalc> G1 {x,y|<y,x>}
Error: Unrecognized command 'G1 {x,y|<y,x>}'
Gcalc> quit
``` 
* see 'help' command for supported commands.

To use batch mode, provide the executable with an input file of commands and an output file:
```
gcalc input.txt output.txt
```
To create the python iterface:
``` bash
make libgraph.a
swig -python graph.i -o graph_wrap.c
g++ -DNDEBUG --pedantic-errors -Wall -Werror -I/<your path>/include/python3.Xm -fPIC -shared graph_wrap.c libgraph.a -o _graph.so
```

## Miscellaneous 

[Design diagram](archive/design.pdf)
[Assignment file](archive/Matam_2019-20_Final_Project.pdf)
