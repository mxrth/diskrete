BLATT :=  $(notdir $(shell pwd))

CXX := clang++
CPPFLAGS := -Wall -Wextra --std=c++11 --pedantic -g3

BINDIR := bin
DISTDIR := ../dist
DISTFILE := $(DISTDIR)/$(BLATT).tar.gz

EXECUTABLE := $(BINDIR)/components
OBJECTS := components.o graph.o

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) -o $@ $^

components.o: graph.C components.C

graph.o: graph.C graph.h

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: dist dist-clean

dist-clean: clean
	rm -f $(DISTFILE)

dist: dist-clean
	tar czf $(DISTFILE) .
