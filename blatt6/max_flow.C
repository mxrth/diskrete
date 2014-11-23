#include "graph.h"
#include <set>
#include <stack>

using std::stack;
using std::vector;

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

Graph::EdgeId findUsableEdge(Graph::NodeId node, Graph &G, vector<bool> &flow, vector<bool> &visited) {
    auto currentNode = G.get_node(node);
    //sammle Kanten
    for (auto eId : currentNode.in_edges()) {
	if (flow[eId] == true) {
	    Graph::NodeId next_node = G.get_edge(eId).get_head();
	    if(!visited[next_node]) {
		return eId;
	    }
	}
    }
    for (auto eId : currentNode.out_edges()) {
	if (flow[eId] == false) {
	    Graph::NodeId next_node = G.get_edge(eId).get_tail();
	    if(!visited[next_node]) {
		return eId;
	    }
	}
    }
    return G.invalid_edge;
}

bool dfs(Graph &G, std::vector<bool> &flow, Graph::NodeId tId, Graph::NodeId sId) {

    stack<Graph::EdgeId, vector<Graph::EdgeId>> path;
    vector<bool> visited(G.num_nodes(), false);

    Graph::NodeId cur = sId;
    visited[sId] = true;

    while(cur != tId) {
	Graph::EdgeId e = findUsableEdge(cur, G, flow, visited);
	if(e != G.invalid_edge) {
	    flow[e] = !flow[e];
	    path.push(e);
	    cur = getOtherNode(G, e, cur);
	    visited[cur] = true;
	} else if(e == G.invalid_edge && cur != sId) {
	    Graph::EdgeId prevEdge = path.top();
	    path.pop();
	    flow[prevEdge] = !flow[prevEdge];
	    Graph::NodeId prevNode = getOtherNode(G, prevEdge, cur);
	    cur = prevNode;
	} else {
	    return false;
	}
    }
    return true;
}


int get_max_flow(Graph &G, Graph::NodeId s, Graph::NodeId tId) {

	std::vector<bool> flow(G.num_edges(), false);
	int anzahlWege = 0;

	while (true) {
		if(dfs(G, flow, tId, s)){
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

