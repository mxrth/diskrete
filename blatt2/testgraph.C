// testgraph.C (Read digraph from file and print)

#include "graph.h"

int main(int argc, char* argv[])
{
      if (argc > 1) 
      {
            Graph g = read_graph(argv[1]);
            print_graph(g);
      }
      return 0;
}
