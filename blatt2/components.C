// testgraph.C (Read digraph from file and print)

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
	    std::cout << "Psi^-1:\n";
	    for(auto i : psi_inverse)
		std::cout << i << ", ";
	    std::cout << "\n";

	    std::fill(visited.begin(), visited.end(), false);
	    Graph::NodeId k=0;
	    comp_type components;

	    for(Graph::NodeId i = g.num_nodes()-1; i > 0; i--) {
		if(!visited[ psi_inverse[i] ] ) {
		    visit2(g, psi_inverse[i], visited,k,  components);
		    k++;
		}
	    }
	    std::cout << "Number of components: " << components.size() << "\n";
	    print_solution(components);

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
    std::cout << "N=" << N << "\n";
    psi_inverse[N] = v;
    N++;
}


void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k, comp_type &components) {
    visited[v] = true;
    for(auto e : g.get_node(v).in_edges()) {
	auto w = g.get_edge(e).get_tail();
	if(!visited[w])
	    visit2(g, w, visited, k, components);
    }
    // size=0, k=0 ==> 0 < 1 ==> size=1 ==> components[k] OK
    // size=4, k=3 ==> 4 !< 4 ==> size=4 ==> components[3] OK
    std::cout << "k=" << k << "\n" << "size=" << components.size() << "\n";
    while(k >= components.size() ) components.push_back(new vector<Graph::NodeId>);
    std::cout << "k=" << k << "\n" << "size=" << components.size() << "\n";
    components[k]->push_back(v);
}




