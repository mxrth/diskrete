#include "max_flow.h"
#include "graph.h"

using std::vector;

void to_digraph(Graph& G) {
	Graph::EdgeId lastEdgeId = G.num_edges();
	for (Graph::NodeId eId = 0; eId < lastEdgeId; eId++) {
		auto e = G.get_edge(eId);
		auto v = e.get_tail();
		auto w = e.get_head();
		Graph::NodeId top = G.add_node();
		Graph::NodeId bot = G.add_node();
		G.change_head(eId, top);
		G.add_edge(top, bot);
		G.add_edge(w, top);
		G.add_edge(bot, v);
		G.add_edge(bot, w);
	}
}

void preprocess(Graph& G) {
	Graph::NodeId last_original_node = G.num_nodes() - 1;
	to_digraph(G);
//range over all nodes of the original graph (except s (=0) and t(=1))
//for each node w, insert a new node v
//add a node e=(v,w)
//for each incoming node of w, change the head of that edge to v
	for (Graph::NodeId w = 2; w <= last_original_node; w++) {
		auto v = G.add_node();
		for (auto incoming : G.get_node(w).in_edges()) {
			G.change_head(incoming, v);
		}
		G.add_edge(v, w);
	}
}

int main(int argc, char* argv[]) {
	bool debug = false;
	if (argc > 3) {
		std::cout << "Usage: " << argv[0] << " <graph_file>\n";
	}
	if (argc == 3)
		debug = true;

	std::cout << "DEBUG = " << debug << std::endl;

	Graph G = read_graph(argv[1]);

	if (!debug){
		preprocess(G);
	}

	print_graph(G);

	std::cout << "Number of disjoint paths: " << get_max_flow(G, 0, 1)
			<< std::endl;
}
