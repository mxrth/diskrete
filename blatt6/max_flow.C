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
		std::set<Graph::NodeId> &visited, Graph::NodeId currentNodeId) {
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
		if (visited.find(wId) != visited.end()) {
			continue;
		}
		flow[eId] = !flow[eId];
		visited.insert(wId);
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
	std::set<Graph::NodeId> visited;
	std::vector<bool> flow(G.num_nodes(), 0);
	int anzahlWege = 0;

	while (true) {
		visited.clear();
		visited.insert(s);
		if(dfs(G, flow, tId, visited, s)){
			anzahlWege++;
		}else{
			return anzahlWege;
		}
	}
}
