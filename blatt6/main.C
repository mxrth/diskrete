#include "max_flow.h"
#include "graph.h"

using std::vector;

void deleteDublicate(Graph& G) {
	//"remove" dublicate edges
	auto deadNode = G.add_node();
	for (auto v : G._nodes) {
		std::vector<bool> visited(G.num_nodes(), false);
		for (auto eId : v.out_edges()) {
			if (visited[G.get_edge(eId).get_head()]) {
				G.change_head(eId, deadNode);
			} else {
				visited[G.get_edge(eId).get_head()] = true;
			}
		}
	}
}

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
	deleteDublicate(G);
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

void assert(bool value, std::string message) {
	if (!value) {
		std::cout << "ERROR: " << message << "\n";
	}
}

void testChangeHead() {
	Graph::EdgeId eId = 1;
	Graph::NodeId tailId = 0, oldHeadId = 1, newHeadId = 2;

	Graph G(3);
	G.add_edge(0, 1);
	G.add_edge(tailId, oldHeadId); //THE edge
	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.change_head(eId, newHeadId);
	auto e = G.get_edge(eId);
	auto newHead = G.get_node(newHeadId);
	auto oldHead = G.get_node(oldHeadId);
	auto tail = G.get_node(tailId);
	assert(e.get_tail() == 0,
			"Tail should not change");
	assert(e.get_head() == newHeadId,
			"Head should change");
	assert(newHead.in_edges().size() == 2,
			"Num in edges of new head");
	assert(newHead.in_edges()[1] == eId,
			"In edges of new head correct");
	assert(newHead.out_edges().size() == 0,
			"Num out edges of new head should not change");
	assert(oldHead.in_edges().size() == 2,
			"Num in edges of old head should change");
	assert(oldHead.out_edges().size() == 0,
			"Num out edges of old head should not change");
	assert(oldHead.in_edges()[0] != eId,
			"Edge should not be in inEdges of old head");
	assert(oldHead.in_edges()[1] != eId,
			"Edge should not be in inEdges of old head");
	assert(tail.out_edges()[1] == eId,
			"Edge should still be out edge of tail");
	assert(tail.out_edges().size() == 4,
			"Num out edges of tail should be correct");
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
	testChangeHead();

	if (!debug) {
		preprocess(G);
	}

	std::cout << "Number of disjoint paths: " << get_max_flow(G, 0, 1)
			<< std::endl;
}
