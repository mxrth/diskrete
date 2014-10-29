#include "graph.h"

#include <vector>
#include <algorithm> //for std::fill

using std::vector; 

//comp_type is the data-structure where the strongly-connected components are stored
typedef vector< vector<Graph::NodeId>* > comp_type;

void visit1(Graph &g, Graph::NodeId v, vector<bool> &visited, vector<Graph::NodeId> &psi_inverse);
void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k,comp_type &components);
void print_solution(comp_type &comps);

int main(int argc, char* argv[])
{
      if (argc > 1) 
      {
            Graph g = read_graph(argv[1]);

	    vector<bool> visited(g.num_nodes(), false); //at the beginning, no node is visited
	    // it suffices to store psi^-1, psi is acutally never needed directly
	    vector<Graph::NodeId> psi_inverse(g.num_nodes(), 0); 
	    
	    //First walk through G, building up psi_inverse
	    for(Graph::NodeId v = 0; v < g.num_nodes(); v++) {
		if(!visited[v]) visit1(g, v, visited, psi_inverse);
	    }

	    std::fill(visited.begin(), visited.end(), false); //reset visited
	    Graph::NodeId k=0; //number of the current strongly-conn. component
	    comp_type components;
	    
	    //Second walk through G, this time backwards, 
	    //starting with the node with the greatest psi-value
	    for(Graph::NodeId i = g.num_nodes(); i-->0;) {
		if(!visited[ psi_inverse[i] ] ) {
		    visit2(g, psi_inverse[i], visited,k,  components);
		    k++; //after visit2 the next call will find a new component
		    //incrementing _after_ visit2, because we start numbering at 0, not at 1
		}
	    }
	   print_solution(components);
	   //free the components vector (inner vectors were allocated by visit2)
	   for(auto c : components)
		delete c;
      }
      return 0;
}

void print_solution(comp_type &comps) {
    std::cout << comps.size() << "\n";
    for(auto c : comps) {
	std::sort(c->begin(), c->end()); //output is required to be sorted
	for(auto v : *c) {
	    std::cout << v << " "; //Specification does not say anything about trailing newlines
	}
	std::cout << "\n";
    }
}

void visit1(Graph &g, Graph::NodeId v, vector<bool> &visited, vector<Graph::NodeId> &psi_inverse) {
    //N is the current psi value
    //it has to be made static since later calls to visit1 has to have access to this value
    static size_t N = 0;
    visited[v] = true;
    auto node = g.get_node(v);
    for(auto e : node.out_edges()) {
	auto w = g.get_edge(e).get_head();
	if(!visited[w])
	    visit1(g, w, visited, psi_inverse);
    }
    //because we start numbering at 0 we first set psi, then increment N
    psi_inverse[N] = v;
    N++;
}


void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k, comp_type &components) {
    visited[v] = true;
    for(auto e : g.get_node(v).in_edges()) {
	auto w = g.get_edge(e).get_tail(); //walk in the opposite direction
	if(!visited[w])
	    visit2(g, w, visited, k, components);
    }
    //make sure there is enough space for the (possibly new) str.con. component
    //The vectors for the components are allocated via `new` so they aren't lost when the func. returns
    while(k >= components.size() ) components.push_back(new vector<Graph::NodeId>);
    components[k]->push_back(v);
}




