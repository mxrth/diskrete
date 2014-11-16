#ifndef MAX_FLOW_H
#define MAX_FLOW_H

//expects a directed graph with the costs of all edges being one
//and calculates the maximum flow in this graph
int get_max_flow(Graph &G, Graph::NodeId s, Graph::NodeId tId);

#endif
