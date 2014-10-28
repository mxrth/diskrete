#include "graph.h"

#include <vector>
#include <algorithm> //for std::fill

using std::vector; 

typedef vector< vector<Graph::NodeId>* > comp_type;

void visit1(Graph &g, Graph::NodeId v, vector<bool> &visited, vector<Graph::NodeId> &psi_inverse);
void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k,comp_type &components);
void print_solution(comp_type &comps);

int main(int argc, char* argv[])
{
      if (argc > 1) 
      {
            Graph g = read_graph(argv[1]);

	    vector<bool> visited(g.num_nodes(), false);
	    vector<Graph::NodeId> psi_inverse(g.num_nodes(), 0);

	    for(Graph::NodeId v = 0; v < g.num_nodes(); v++) {
		if(!visited[v]) visit1(g, v, visited, psi_inverse);
	    }

	    for(auto v : visited) {
		if(!v) std::cout << "ERROR\n";
	    }
	    std::fill(visited.begin(), visited.end(), false);
	    Graph::NodeId k=0;
	    comp_type components;
	    /*
	    for(size_t i = 0; i < psi_inverse.size(); i++) {
		std::cout << "psi_inverse[" << i << "] = " << psi_inverse[i] << std::endl;
	    }*/
	    
	    for(Graph::NodeId i = g.num_nodes(); i-->0;) {
		if(!visited[ psi_inverse[i] ] ) {
		    visit2(g, psi_inverse[i], visited,k,  components);
		    k++;
		}
	    }
	    /*for(size_t i=0; i < visited.size(); i++) {
		if(!visited[i]) std::cout << "ERROR at " << i << std::endl;
	    }*/
	    print_solution(components);
	    for(auto c : components)
		delete c;
      }
      return 0;
}

void print_solution(comp_type &comps) {
    std::cout << comps.size() << "\n";
    for(auto c : comps) {
	std::sort(c->begin(), c->end());
	for(auto v : *c) {
	    std::cout << v << " ";
	}
	std::cout << "\n";
    }
}

void visit1(Graph &g, Graph::NodeId v, vector<bool> &visited, vector<Graph::NodeId> &psi_inverse) {
    static size_t N = 0;
    visited[v] = true;
    auto node = g.get_node(v);
    for(auto e : node.out_edges()) {
	auto w = g.get_edge(e).get_head();
	if(!visited[w])
	    visit1(g, w, visited, psi_inverse);
    }
    psi_inverse[N] = v;
    N++;
}


void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k, comp_type &components) {
    //std::cout << "VISIT2(" << v << ")\n";
    visited[v] = true;
    for(auto e : g.get_node(v).in_edges()) {
	auto w = g.get_edge(e).get_tail();
	if(!visited[w])
	    visit2(g, w, visited, k, components);
    }
    while(k >= components.size() ) components.push_back(new vector<Graph::NodeId>);
    components[k]->push_back(v);
}




