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

	std::vector<bool> flow(G.num_edges(), false);
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

int countTotalFlow(Graph &G, std::vector<bool> &flow){
	int sum = 0;
	for(Graph::NodeId eId = 0; eId < G.num_edges(); eId++){
		sum += flow[eId];
	}
	return sum;
}

int countOutFlow(Graph &G, Graph::NodeId s, std::vector<bool> &flow){
	int sum = 0;
	for(auto eId : G.get_node(s).out_edges()){
		sum += flow[eId];
	}
	return sum;
}

int countInFlow(Graph &G, Graph::NodeId s, std::vector<bool> &flow){
	int sum = 0;
	for(auto eId : G.get_node(s).in_edges()){
		sum += flow[eId];
	}
	return sum;
}

int checkIntegrity(Graph &G, std::vector<bool> &flow){
	if(countInFlow(G,1, flow) != countOutFlow(G, 0, flow)){
		return 1;
	}
	for(Graph::NodeId vId = 2; vId < G.num_nodes(); vId++){
		if(countInFlow(G, vId, flow) != countOutFlow(G, vId, flow)){
			return 2;
		}
	}
	for(Graph::NodeId vId = 2; vId < G.num_nodes(); vId++){
		if(countInFlow(G, vId, flow) > 1){
			return 3;
		}
	}
	return 0;
}

