#include <iostream>
#include <stdexcept>
#include <limits>

#include "graph.h"
#include "wgraph.h"

using std::vector;

Graph::NodeId add_connected_node(Weighted_Graph &g);
void moore_bellman_ford(Weighted_Graph &g, Graph::NodeId start);

int main(int argc, char* argv[]) {
    if(argc <= 1) {
	std::cout << "Usage: " << argv[0] << " <graph_file>" << std::endl;
    }
    try {
	Weighted_Graph g(argv[1], true); 
	Graph::NodeId s = add_connected_node(g);
	vector<Graph::NodeId> l(g.num_nodes(), std::numeric_limits<Graph::NodeId>::max());
	vector<Graph::NodeId> p(g.num_nodes());
	vector<Graph::NodeId> changed;
	changed.push_back(s);
	l[s] = 0;
	for(Graph::NodeId i = 1; i < g.num_nodes(); i++) {
	    vector<Graph::NodeId> tmp_changed;
	    std::cout << "New iteration\n";
	    for(auto v : changed) {
		std::cout << "Visited node " << v << std::endl;
		for(auto edge : g.get_node(v).out_edges()) {
		    Graph::NodeId w = g.get_edge(edge).get_head();
		    if(l[w] > l[v] + g._weight[edge]) {
			l[w] = l[v] + g._weight[edge];
			p[w] = v;
			tmp_changed.push_back(w);
		    }
		}
	    }
	    changed = tmp_changed;
	}
	if(changed.size() > 0) {
	    std::cout << "Found negative circle, now what?" << std::endl;
	}
	else {
	    std::cout << "1\n";
	    for(auto p : l)
		std::cout << p << std::endl;
	}
	
	//g.print();			
    } catch(std::runtime_error e) {
	std::cout << "Error: " << e.what() << " while reading input file " << argv[1] << std::endl;
    }
   return 0; 
}


Graph::NodeId add_connected_node(Weighted_Graph &g) {
    Graph::NodeId s = g.add_node();
    for(Graph::NodeId node = 0; node < g.num_nodes(); node++) {
	if(node != s) {
	    g.add_edge(s, node);
	    g._weight.push_back(0);
	}
    }
    return s;
}
