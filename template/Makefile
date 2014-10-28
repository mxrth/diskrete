CXX = clang++
CPPFLAGS = -Wall -Wextra --std=c++11

BINDIR = bin

EXECUTABLE = testgraph
OBJECTS = testgraph.o graph.o

$(EXECUTABLE): testgraph.o graph.o
	$(CXX) -o $(BINDIR)/$@ $^

testgraph.o: graph.h testgraph.C

graph.o: graph.C graph.h

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) $(OBJECTS)
