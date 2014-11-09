#include <iostream>
#include <stdexcept>
#include <limits>
#include <set>

#include "graph.h"
#include "wgraph.h"

using std::vector;
using std::set;

Graph::NodeId add_connected_node(Weighted_Graph &g);
void moore_bellman_ford(Weighted_Graph &g, Graph::NodeId start);

int main(int argc, char* argv[]) {
    if(argc <= 1) {
	std::cout << "Usage: " << argv[0] << " <graph_file>" << std::endl;
    }
    try {
	Weighted_Graph g(argv[1], true); 
	Graph::NodeId s = add_connected_node(g);
	vector<double> l(g.num_nodes(), std::numeric_limits<double>::max());
	vector<Graph::NodeId> p(g.num_nodes());
	set<Graph::NodeId> changed;
	changed.insert(s);
	l[s] = 0;
	for(Graph::NodeId i = 1; i < g.num_nodes(); i++) {
	    set<Graph::NodeId> tmp_changed;
	    for(auto v : changed) {
		for(auto edge : g.get_node(v).out_edges()) {
		    Graph::NodeId w = g.get_edge(edge).get_head();
		    if(l[w] > l[v] + g._weight[edge]) {
			l[w] = l[v] + g._weight[edge];
			p[w] = v;
			tmp_changed.insert(w);
		    }
		}
	    }
	    changed = tmp_changed;
	}
	if(changed.size() > 0) {
	    std::cout << "0\n";
	    std::cout << "Found negative circle, now what?" << std::endl;
	}
	else {
	    std::cout << "1\n";
	    for(Graph::NodeId i = 0; i < l.size()-1; i++) 
		std::cout << l[i] << std::endl;
	}
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
