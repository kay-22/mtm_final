CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++

GRPH_H = graph/Vertex.h \
	graph/Graph.h\
	graph.h

GCLC_H = g_calc/GraphCalculator.h \
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
	Vertex.o \
	graph.o

EXEC = gcalc
LIB = libgraph.a
RELEASE =-DNDEBUG
DEBUG =#-g
COMP = -std=c++11 -Wall -Werror -pedantic-errors -fPIC

${EXEC} : ${OBJS}
	${CXX} ${DEBUG} ${OBJS} -o $@

#g++ -std=c++11 -I. -MM main.cpp g_calc/GraphCalculator.cpp g_calc/Instruction.cpp g_except/Exception.cpp g_except/GraphException.cpp g_except/InstructionException.cpp g_except/NameException.cpp g_except/ParserException.cpp g_utility/GCFileName.cpp g_utility/GraphName.cpp g_utility/Name.cpp g_utility/Parser.cpp g_utility/VertexName.cpp graph/Graph.cpp graph/Vertex.cpp

main.o: main.cpp g_calc/GraphCalculator.h graph/Graph.h graph/Vertex.h \
 g_utility/VertexName.h g_utility/Name.h g_except/NameException.h \
 g_except/Exception.h g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h g_utility/GraphName.h \
 g_except/GraphException.h g_utility/Parser.h g_except/Exception.h \
 g_calc/Instruction.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} main.cpp

GraphCalculator.o: g_calc/GraphCalculator.cpp g_calc/GraphCalculator.h \
 graph/Graph.h graph/Vertex.h g_utility/VertexName.h g_utility/Name.h \
 g_except/NameException.h g_except/Exception.h g_utility/Parser.h \
 g_except/ParserException.h g_except/InstructionException.h \
 g_utility/GraphName.h g_except/GraphException.h g_utility/Parser.h \
 g_except/Exception.h g_calc/Instruction.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_calc/GraphCalculator.cpp

Instruction.o: g_calc/Instruction.cpp g_calc/Instruction.h graph/Graph.h \
 graph/Vertex.h g_utility/VertexName.h g_utility/Name.h \
 g_except/NameException.h g_except/Exception.h g_utility/Parser.h \
 g_except/ParserException.h g_except/InstructionException.h \
 g_utility/GraphName.h g_except/GraphException.h g_utility/Parser.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_calc/Instruction.cpp

Exception.o: g_except/Exception.cpp g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/Exception.cpp

GraphException.o: g_except/GraphException.cpp g_except/GraphException.h \
 g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/GraphException.cpp

InstructionException.o: g_except/InstructionException.cpp \
 g_except/InstructionException.h g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/InstructionException.cpp

NameException.o: g_except/NameException.cpp g_except/NameException.h \
 g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/NameException.cpp

ParserException.o: g_except/ParserException.cpp \
 g_except/ParserException.h g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/ParserException.cpp

GCFileName.o: g_utility/GCFileName.cpp g_utility/GCFileName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/GCFileName.cpp

GraphName.o: g_utility/GraphName.cpp g_utility/GraphName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/GraphName.cpp

Name.o: g_utility/Name.cpp g_utility/Name.h g_except/NameException.h \
 g_except/Exception.h g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/Name.cpp

Parser.o: g_utility/Parser.cpp g_utility/Parser.h \
 g_except/ParserException.h g_except/Exception.h \
 g_except/InstructionException.h g_calc/Instruction.h graph/Graph.h \
 graph/Vertex.h g_utility/VertexName.h g_utility/Name.h \
 g_except/NameException.h g_utility/Parser.h g_utility/GraphName.h \
 g_except/GraphException.h g_utility/Parser.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/Parser.cpp

VertexName.o: g_utility/VertexName.cpp g_utility/VertexName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/VertexName.cpp

Graph.o: graph/Graph.cpp graph/Graph.h graph/Vertex.h \
 g_utility/VertexName.h g_utility/Name.h g_except/NameException.h \
 g_except/Exception.h g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h g_utility/GraphName.h \
 g_except/GraphException.h g_utility/Parser.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} graph/Graph.cpp

Vertex.o: graph/Vertex.cpp graph/Vertex.h g_utility/VertexName.h \
 g_utility/Name.h g_except/NameException.h g_except/Exception.h \
 g_utility/Parser.h g_except/ParserException.h \
 g_except/InstructionException.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} graph/Vertex.cpp

graph.o: graph.cpp graph.h graph/Graph.h graph/Vertex.h \
 graph/../g_utility/VertexName.h graph/../g_utility/Name.h \
 graph/../g_utility/../g_except/NameException.h \
 graph/../g_utility/../g_except/Exception.h graph/../g_utility/Parser.h \
 graph/../g_utility/../g_except/ParserException.h \
 graph/../g_utility/../g_except/InstructionException.h \
 graph/../g_utility/GraphName.h graph/../g_except/GraphException.h \
 graph/../g_except/Exception.h graph/../g_utility/Parser.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} graph.cpp

${LIB} : ${OBJS}
	ar -rs $@ $^

tar:
	make clean
	zip -r ${EXEC}.zip .

clean:
	rm -f ${OBJS} ${EXEC} ${EXEC}.zip ${LIB}