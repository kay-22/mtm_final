CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++

GRPH_H = graph/Vertex.h \
    graph/Graph.h \
    GraphCalculator.h

UTL_H = g_utility/Name.h \
    g_utility/VertexName.h \
    g_utility/GraphName.h \
    g_utility/GCFileName.h \
    g_utility/Parser.h

EXCEPT_H = g_except/Exception.h \
    g_except/NameException.h \
    g_except/GraphException.h

TST_H = g_test/GCTest.h \
    g_test/GraphTest.h

OBJS = main.o \
	GraphCalculator.o \
	Graph.o \
	Vertex.o \
	GraphName.o \
	VertexName.o \
	GCFileName.o \
	Name.o \
	Parser.o \
	Exception.o \
	NameException.o \
	GraphException.o \
	GraphTest.o \
	GCTest.o

INC = -I${CURDIR}
EXEC = gcalc
RELEASE = -DNDEBUG
DEBUG =#-g
COMP = -std=c++11 -Wall -Werror -pedantic-errors

${EXEC} : ${OBJS}
	${CXX} ${DEBUG} ${OBJS} -o $@

main.o : main.cpp ${GRPH_H} ${UTL_H} ${EXCEPT_H} ${TST_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} $.cpp

GraphCalculator.o : GraphCalculator.cpp GraphCalculator.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} $.cpp

Graph.o : graph/Graph.cpp graph/Graph.h ${UTL_H} ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} graph/Graph.cpp

Vertex.o : graph/Vertex.cpp graph/Vertex.h ${UTL_H} ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} graph/Vertex.cpp

GraphName.o : g_utility/GraphName.cpp g_utility/GraphName.h g_utility/Name.h g_utility/Parser.h ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/GraphName.cpp

VertexName.o : g_utility/VertexName.cpp g_utility/VertexName.h g_utility/Name.h g_utility/Parser.h ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/VertexName.cpp

GCFileName.o : g_utility/GCFileName.cpp g_utility/GCFileName.h g_utility/Name.h g_utility/Parser.h ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/GCFileName.cpp

Name.o : g_utility/Name.cpp g_utility/Name.h g_utility/Parser.h ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/Name.cpp

Parser.o : g_utility/Parser.cpp g_utility/Parser.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_utility/Parser.cpp

Exception.o : g_except/Exception.cpp g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/Exception.cpp

NameException.o : g_except/NameException.cpp g_except/NameException.h g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/NameException.cpp

GraphException.o : g_except/GraphException.cpp g_except/GraphException.h g_except/Exception.h
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_except/GraphException.cpp

GraphTest.o : g_test/GraphTest.cpp g_test/GraphTest.h ${GRPH_H} ${UTL_H} ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_test/GraphTest.cpp

GCTest.o : g_test/GCTest.cpp g_test/GCTest.h# ${GRPH_H} ${UTL_H} ${EXCEPT_H}
	${CXX} -c ${DEBUG} ${COMP} ${RELEASE} g_test/GraphTest.cpp

clean:
	rm -f ${OBJS} ${EXEC}