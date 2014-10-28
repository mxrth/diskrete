// testgraph.C (Read digraph from file and print)

#include "graph.h"

#include <vector>
#include <algorithm> //for std::fill

using std::vector; 

typedef vector<*(vector<Graph::NodeId>)> comp_type;

void visit1(Graph &g, Graph::NodeId v, vector<bool> &visited, vector<Graph::NodeId> &psi_inverse);
void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k,compt_type components);

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

	    std::fill(visited.begin(), visited.end(), false);
	    Graph::NodeId k=0;
	    comp_type components;

	    for(Graph::NodeId i = g.num_nodes(); i > 0; i--) {
		if(!visited[ psi_inverse[i] ] ) {
		    k++;
		    visit2(g, psi_inverse[i], visited,k,  components);
		}
	    }
	    std::cout << "Number of components: " << components.size() << "\n";

      }
      return 0;
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
    N++;
    psi_inverse[N] = v;
}


void visit2(Graph &g, Graph::NodeId v, vector<bool> &visited, size_t k, comp_type components) {
    visited[v] = true;
    for(auto e : g.get_node(v).in_edges()) {
	auto w = g.get_edge(e).get_tail();
	if(!visited[w])
	    visit2(g, w, visited, k, components);
    }
    if(components.size() < k)
	components.push_back(new vector<Graph::NodeId>());
    components[k].push_back(v);
}




