CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++

GRPH_H = graph/Vertex.h \
    graph/Graph.h

GCLC_H = g_calc/GraphCalculator.h \
	g_calc/Expression.h \
	g_calc/Instruction.h

UTL_H = g_utility/Name.h \
    g_utility/VertexName.h \
    g_utility/GraphName.h \
    g_utility/GCFileName.h \
    g_utility/Parser.h

EXCEPT_H = g_except/Exception.h \
    g_except/NameException.h \
    g_except/GraphException.h \
	g_except/InstructionException.h \
	g_except/ParserException.h

OBJS = main.o \
	GraphCalculator.o \
	Expression.o \
	Instruction.o \
	Exception.o \
	GraphException.o \
	InstructionException.o \
	NameException.o \
	ParserException.o \
	GCFileName.o \
	GraphName.o \
	Name.o \
	Parser.o \
	VertexName.o \
	Graph.o \
	Vertex.o

INC = -I${CURDIR}
EXEC = gcalc
RELEASE =-DNDEBUG
DEBUG =#-g
COMP = -std=c++11 -Wall -Werror -pedantic-errors

${EXEC} : ${OBJS}
	${CXX} ${DEBUG} ${OBJS} -o $@

#g++ -std=c++11 -I. -MM main.cpp g_calc/GraphCalculator.cpp g_calc/Expression.cpp g_calc/Instruction.cpp g_except/Exception.cpp g_except/GraphException.cpp g_except/InstructionException.cpp g_except/NameException.cpp g_except/ParserException.cpp g_utility/GCFileName.cpp g_utility/GraphName.cpp g_utility/Name.cpp g_utility/Parser.cpp g_utility/VertexName.cpp graph/Graph.cpp graph/Vertex.cpp

main.o: main.cpp g_calc/GraphCalculator.h graph/Graph.h graph/Vertex.h \
 g_utility/VertexName.h g_utility/Name.h g_except/NameException.h \
 g_except/Exception.h g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h g_utility/GraphName.h \
 g_except/GraphException.h g_utility/Parser.h g_except/Exception.h \
 g_calc/Instruction.h
GraphCalculator.o: g_calc/GraphCalculator.cpp g_calc/GraphCalculator.h \
 graph/Graph.h graph/Vertex.h g_utility/VertexName.h g_utility/Name.h \
 g_except/NameException.h g_except/Exception.h g_utility/Parser.h \
 g_except/ParserException.h g_except/InstructionException.h \
 g_utility/GraphName.h g_except/GraphException.h g_utility/Parser.h \
 g_except/Exception.h g_calc/Instruction.h
Expression.o: g_calc/Expression.cpp
Instruction.o: g_calc/Instruction.cpp g_calc/Instruction.h graph/Graph.h \
 graph/Vertex.h g_utility/VertexName.h g_utility/Name.h \
 g_except/NameException.h g_except/Exception.h g_utility/Parser.h \
 g_except/ParserException.h g_except/InstructionException.h \
 g_utility/GraphName.h g_except/GraphException.h g_utility/Parser.h
Exception.o: g_except/Exception.cpp g_except/Exception.h
GraphException.o: g_except/GraphException.cpp g_except/GraphException.h \
 g_except/Exception.h
InstructionException.o: g_except/InstructionException.cpp \
 g_except/InstructionException.h g_except/Exception.h
NameException.o: g_except/NameException.cpp g_except/NameException.h \
 g_except/Exception.h
ParserException.o: g_except/ParserException.cpp \
 g_except/ParserException.h g_except/Exception.h
GCFileName.o: g_utility/GCFileName.cpp g_utility/GCFileName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
GraphName.o: g_utility/GraphName.cpp g_utility/GraphName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
Name.o: g_utility/Name.cpp g_utility/Name.h g_except/NameException.h \
 g_except/Exception.h g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
Parser.o: g_utility/Parser.cpp g_utility/Parser.h \
 g_except/ParserException.h g_except/Exception.h \
 g_except/InstructionException.h g_calc/Instruction.h graph/Graph.h \
 graph/Vertex.h g_utility/VertexName.h g_utility/Name.h \
 g_except/NameException.h g_utility/Parser.h g_utility/GraphName.h \
 g_except/GraphException.h g_utility/Parser.h
VertexName.o: g_utility/VertexName.cpp g_utility/VertexName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
Graph.o: graph/Graph.cpp graph/Graph.h graph/Vertex.h \
 g_utility/VertexName.h g_utility/Name.h g_except/NameException.h \
 g_except/Exception.h g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h g_utility/GraphName.h \
 g_except/GraphException.h g_utility/Parser.h
Vertex.o: graph/Vertex.cpp graph/Vertex.h g_utility/VertexName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h

#libgraph.a :
#	asdsda

tar:
	zip -r ${EXEC}.zip .

clean:
	rm -f ${OBJS} ${EXEC} ${EXEC}.zip