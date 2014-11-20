#include "max_flow.h"
#include "graph.h"

using std::vector;
using Graph::NodeId, Graph::EdgeId;

Graph &to_digraph(Graph& G);
Graph &preprocess(Graph& G);

int main(int argc, char* argv[]) {
    
}


Graph &to_digraph(Graph& G) {
    vector<bool> visited(G.num_nodes(), false);
    NodeId last_node = G.num_nodes()-1;
    for(v = 0; v < last_node; v++) {
	visited[v] = true;
	for(auto e : G.get_node(v).out_edges()) {
	    for(auto w : e) {
		if(visted[w] || w > last_node) 
		    continue;
		visited[w] = true;

		NodeId top = G.add_node();
		NodeId bot = G.add_node();
		G.add_edge(v, top);
		G._edges[]
		G.add_edge(top, bot);
		G.add_edge(w, top);
		G.add_edge(bot, v);
	    }
	}
    }
}

Graph &preprocess(Graph& G) {
    NodeId s = 0;
    NodeId t = 1;
    NodeId last_original_node = G.num_nodes()-1;
    G = to_digraph(G);
    for(int v = 0; v <= last_original_node; v++) {
	auto new_node = G.add_node();
	G.add_edge(v, new_node);
    }
}
