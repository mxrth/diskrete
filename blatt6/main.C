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
				auto e = G.get_edge(eId);
				for(auto e2Id : G.get_node(e.get_head()).out_edges()){
					if(G.get_edge(e2Id).get_head() == e.get_tail()){
						G.change_head(e2Id, deadNode);
					}
				}
			}
		}
	}
}


void preprocess(Graph& G) {
    Graph::NodeId lastNodeId = G.num_nodes() - 1;
    Graph::EdgeId lastEdgeId = G.num_edges() - 1;
    vector<Graph::NodeId> lower_nodeId(G.num_nodes(), G.invalid_node);
    for(Graph::NodeId vId = 0; vId <= lastNodeId; vId++) {
	lower_nodeId[vId] = G.add_node();
	G.add_edge(vId, lower_nodeId[vId]);
    }
    for(Graph::EdgeId eId = 0; eId <= lastEdgeId; eId++) {
	auto e = G.get_edge(eId);
	auto head = e.get_head();
	auto tail = e.get_tail();
	G.change_tail(eId, lower_nodeId[tail]);
	G.add_edge(lower_nodeId[head], tail);
    }
}

void assert(bool value, std::string message) {
	if (!value) {
		std::cout << "ERROR: " << message << "\n";
	}
}

//ID of THE edge will be 1
Graph setupTestGraph(Graph::NodeId tailId, Graph::NodeId oldHeadId){
	Graph G = read_graph("/home/bk/git/diskrete_max/blatt6/test/inst_02_new");
	return G;
}

void testChangeHead() {
	Graph::EdgeId eId = 1;
	Graph::NodeId tailId = 0, oldHeadId = 131, newHeadId = 2;
	auto G1 = setupTestGraph(tailId, oldHeadId);
	auto G2 = setupTestGraph(tailId, oldHeadId); //G2 will be modified
	G2.change_head(eId, newHeadId);

	auto e2 = G2.get_edge(eId);
	auto newHead1 = G1.get_node(newHeadId);
	auto newHead2 = G2.get_node(newHeadId);
	auto oldHead1 = G1.get_node(oldHeadId);
	auto oldHead2 = G2.get_node(oldHeadId);
	auto tail1 = G1.get_node(tailId);
	auto tail2 = G2.get_node(tailId);

	assert(e2.get_tail() == tailId,
			"Tail should not change");
	assert(e2.get_head() == newHeadId,
			"Head should change");
	assert(newHead2.in_edges().size() == newHead1.in_edges().size() + 1,
			"Num in edges of new head");
	assert(newHead2.in_edges()[newHead2.in_edges().size()-1] == eId,
			"In edges of new head correct");
	assert(newHead2.out_edges().size() == newHead1.out_edges().size() ,
			"Num out edges of new head should not change");
	assert(oldHead2.in_edges().size() == oldHead1.in_edges().size() - 1,
			"Num in edges of old head should change");
	assert(oldHead2.out_edges().size() == oldHead1.out_edges().size(),
			"Num out edges of old head should not change");
	for(auto inEdgeId : oldHead2.in_edges()){
		assert(inEdgeId != eId,
				"Edge should not be in inEdges of old head");
	}
	assert(tail2.out_edges().size() == tail1.out_edges().size(),
			"Num out edges of tail should not change");
}

int main(int argc, char* argv[]) {
	bool debug = false;
	if (argc > 3) {
		std::cout << "Usage: " << argv[0] << " <graph_file>\n";
	}
	if (argc == 3)
		debug = true;

	Graph G = read_graph(argv[1]);
	auto last_nodeId = G.num_nodes() - 1;
	if (!debug) {
		preprocess(G);
	}
	
	//print_graph(G);

	std::cout << get_max_flow(G, last_nodeId + 1, 1) << std::endl;
	return 0;
}
