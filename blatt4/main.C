#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if(argc <= 1) {
	std::cout << "Usage: " << argv[0] << " <graph_file>" << std::endl;
    }
    try {
	Weighted_Graph g(argv[1], true); 
    } catch(std::runtime_error e) {
	std::cout << "Error: " << e.what() << " while reading input file " << argv[1] << std::endl;
    }
    // Add node v with cost-0 edge to every other node
    Graph::NodeId s = g.add_node();
    Graph::EdgeId e;
    for(v : g.nodes) {
	if(v != s) {
	    
	}
    }
}
