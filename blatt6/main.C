#include "max_flow.h"
#include "graph.h"

using std::vector;

Graph &to_digraph(Graph& G);
Graph &preprocess(Graph& G);

int main(int argc, char* argv[]) {
    
}


Graph &to_digraph(Graph& G) {
    vector<bool> visited(G.num_nodes(), false);
    Graph::NodeId last_node = G.num_nodes()-1;
    for(Graph::NodeId v = 0; v < last_node; v++) {
	visited[v] = true;
	for(auto w : G.get_node(v).out_edges()) {
	    if(visited[w] || w > last_node){
	    	continue;
	    }
	    visited[w] = true;

	    Graph::NodeId top = G.add_node();
	    Graph::NodeId bot = G.add_node();
	    G.add_edge(v, top);
	    G.add_edge(top, bot);
	    G.add_edge(w, top);
	    G.add_edge(bot, v);
	}
    }
}

Graph &preprocess(Graph& G) {
    Graph::NodeId s = 0;
    Graph::NodeId t = 1;
    Graph::NodeId last_original_node = G.num_nodes()-1;
    G = to_digraph(G);
}
