#include "graph.h"
#include <set>


/*
 * Gibt für eine gegebene Kante eId und einen Endpunkt vId dieser Kante
 * den anderen Endpunkt der Kante zurück
 */
Graph::NodeId getOtherNode(Graph &G, Graph::EdgeId eId, Graph::NodeId vId) {
	auto e = G.get_edge(eId);
	if (e.get_head() == vId) {
		return e.get_tail();
	}
	return e.get_head();
}


bool dfs(Graph &G, std::vector<bool> &flow, Graph::NodeId tId,
		std::vector<bool> &visited, Graph::NodeId currentNodeId) {
	std::vector<Graph::EdgeId> angrenzendeKanten;

	auto currentNode = G.get_node(currentNodeId);
	//sammle Kanten
	for (auto eId : currentNode.in_edges()) {
		if (flow[eId] == true) {
			angrenzendeKanten.push_back(eId);
		}
	}
	for (auto eId : currentNode.out_edges()) {
		if (flow[eId] == false) {
			angrenzendeKanten.push_back(eId);
		}
	}


	for (Graph::EdgeId eId : angrenzendeKanten) {
		auto wId = getOtherNode(G, eId, currentNodeId);
		if (visited[wId] == true) {
			continue;
		}
		visited[wId] = true;
		flow[eId] = !flow[eId];
		if (wId == tId) {
			return true;
		}
		if (dfs(G, flow, tId, visited, wId)) {
			return true;
		} else {
			//ueber diese kante kommen wir nicht zum ziel -> rueckgaengeig machen
			flow[eId] = !flow[eId];
		}
	}
	return false;
}


int get_max_flow(Graph &G, Graph::NodeId s, Graph::NodeId tId) {

	std::vector<bool> flow(G.num_edges(), 0);
	int anzahlWege = 0;

	while (true) {
		std::vector<bool> visited(G.num_nodes(), false);
		visited[s] = true;
		if(dfs(G, flow, tId, visited, s)){
			anzahlWege++;
		}else{
			return anzahlWege;
		}
	}
}
