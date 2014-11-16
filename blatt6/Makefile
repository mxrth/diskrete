BLATT :=  $(notdir $(shell pwd))

CXX := clang++
CPPFLAGS := -Wall -Wextra --std=c++11 --pedantic -g3

BINDIR := bin
DISTDIR := ../dist
DISTFILE := $(DISTDIR)/$(BLATT)_BenKMaxR.tar.gz

### FILL IN EXECUTABLE AND OBJECTS HERE ###
EXECUTABLE := disjoint_paths 
OBJECTS := graph.o main.o max_flow.o
###########################################

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) -o $@ $^

graph.o: graph.C graph.h

main.o: main.C graph.h max_flow.h

max_flow.o: max_flow.C max_flow.h

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: dist dist-clean

dist-clean: clean
	rm -f $(DISTFILE)

dist: dist-clean
	tar czf $(DISTFILE) .
