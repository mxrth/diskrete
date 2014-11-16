BLATT :=  $(notdir $(shell pwd))

CXX := clang++
CPPFLAGS := -Wall -Wextra --std=c++11 --pedantic -g3

BINDIR := bin
DISTDIR := ../dist
DISTFILE := $(DISTDIR)/$(BLATT)BenKMaxR.tar.gz

### FILL IN EXECUTABLE AND OBJECTS HERE ###
EXECUTABLE := mbf 
OBJECTS := graph.o main.o
###########################################

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(CPPFLAGS) -o $@ $^

graph.o: graph.C graph.h

main.o: main.C graph.h wgraph.h

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: dist dist-clean

dist-clean: clean
	rm -f $(DISTFILE)

dist: dist-clean
	tar czf $(DISTFILE) .
