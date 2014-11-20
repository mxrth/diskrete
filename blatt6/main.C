#include "max_flow.h"
#include "graph.h"

using std::vector;

Graph &to_digraph(Graph& G);
Graph &preprocess(Graph& G);

int main(int argc, char* argv[]) {
    if(argc != 2) {
	std::cout << "Usage: " << argv[0] << " <graph_file>\n";
    }
    Graph G = read_graph(argv[1]); 
    G = preprocess(G);
}


void to_digraph(Graph& G) {
    vector<bool> visited(G.num_nodes(), false);
    Graph::NodeId last_node = G.num_nodes()-1;
    for(Graph::NodeId v = 0; v < last_node; v++) {
	visited[v] = true;
	for(auto e : G.get_node(v).out_edges()) {
	    auto w = G.get_edge(e).get_head();
	    if(visited[w] || w > last_node)
	        continue;
	    visited[w] = true;

	    Graph::NodeId top = G.add_node();
	    Graph::NodeId bot = G.add_node();
	    G.change_head(e, top);
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
    //range over all nodes of the original graph
    //for each node w, insert a new node v
    //add a node e=(v,w)
    //for each incoming node of w, change the head of that edge to v
    for(int w = 0; w <= last_original_node; w++) {
	auto v = G.add_node();
	G.add_edge(v, w);
	for(auto incoming : G.get_node(w).in_edges()) {
	    G.change_head(incoming, v);
	}
    }
}
