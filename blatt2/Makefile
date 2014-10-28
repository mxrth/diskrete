CXX := clang++
CPPFLAGS := -Wall -Wextra --std=c++11 --pedantic -g3

BINDIR := bin

EXECUTABLE := $(BINDIR)/components
OBJECTS := components.o graph.o

$(EXECUTABLE): components.o graph.o
	$(CXX) -o $@ $^

components.o: graph.C components.C

graph.o: graph.C graph.h

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) $(OBJECTS)
