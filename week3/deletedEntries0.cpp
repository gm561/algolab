#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/visitors.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    typedef pair<int, int> E;

    typedef adjacency_list<vecS, vecS, undirectedS,
			     no_property, property <edge_weight_t, int> > Graph;

    typedef graph_traits <Graph>::edge_descriptor Edge;
    typedef graph_traits <Graph>::vertex_descriptor Vertex;

    int TC;
    cin>>TC;

    vector<E> edges;
    vector<int> weights;
    for(int tc = 0; tc < TC; ++tc) {
	int n,m;
	cin>>n>>m;
	edges.resize(m);
	weights.resize(m,1);

	int s0,s1;
	for(int i = 0; i < m; ++i) {
	    cin>>s0>>s1;
	    edges[i] = make_pair(s0,s1);
	}

	//corner cases eg: n < 3, graph not connected.
	Graph g(edges.begin(), edges.end(), weights.begin(), n);

	vector<Vertex> p(n);

	std::vector < Edge > spanning_tree;
	kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

	

    }

    return 0;
}
