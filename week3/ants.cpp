#include <iostream>

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace std;
using namespace boost;


int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    typedef adjacency_list <vecS, vecS, undirectedS,
			     no_property, property <edge_weight_t, int> > Graph;

    typedef graph_traits <Graph>::edge_descriptor edge_desc;
    typedef graph_traits <Graph>::vertex_descriptor vertex_desc;
    typedef property_map<Graph, edge_weight_t>::type weight_map;

    int TC;
    cin>>TC;

    for (int tc = 0; tc < TC; ++tc) {
	int t, e, s, a, b;
	cin>>t>>e>>s>>a>>b;

	vector<Graph> graphs(s, Graph(t));
	vector<weight_map> weights(s);

	for(int i = 0; i < s; ++i) {
	    weights[i] = get(edge_weight, graphs[i]);
	}

	for (int i = 0; i < e; ++i) {
	    int v0,v1;
	    cin>>v0>>v1;
	    for(int j = 0; j < s; ++j) {
		int w;
		cin>>w;
		edge_desc e; bool inserted;
		tie(e, inserted) = add_edge(v0, v1, graphs[j]);
		weights[j][e] = w;
	    }
	}

	vector<int> hives(s);
	for(int i = 0; i < s; ++i) {
	    cin>>hives[i];
	}

	typedef vector <edge_desc> SpanningTree;
	vector<SpanningTree> trees(s);

	for(int i = 0; i < s; ++i)
	    kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(trees[i]));

	vector<int> weight_vector;
	vector<pair<int,int> > edge_vector;

	for(int i = 0; i < s; ++i) {
	    for(int j = 0; j < t-1; ++j) {
		int s = source(trees[i][j], graphs[i]);
		int t = target(trees[i][j], graphs[i]);
		edge_vector.push_back(make_pair(s,t));
		weight_vector.push_back(weights[i][trees[i][j]]);
	    }
	}

	Graph g_sol(edge_vector.begin(), edge_vector.end(), weight_vector.begin(), t);

	vertex_desc source = vertex(a, g_sol);
	std::vector<int> d(num_vertices(g_sol));

	dijkstra_shortest_paths(g_sol, source, distance_map(&d[0]));

	cout<<d[vertex(b,g_sol)] <<"\n";
    }

    return 0;
}

