#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;
using namespace boost::lambda;

int main(int argc, char *argv[]) {
    cin.sync_with_stdio ( false );
    cout.sync_with_stdio ( false );

    typedef adjacency_list < vecS, vecS, undirectedS,
			     no_property, property < edge_weight_t, int > > Graph;

    typedef graph_traits < Graph >::edge_descriptor Edge;
    typedef graph_traits < Graph >::vertex_descriptor Vertex;
    typedef pair<int,int> E;

    int TC;
    cin>>TC;

    vector<E> edge_vector;
    vector<int> weight_vector;

    for (int t = 0; t < TC; ++t) {
	int ver_n;
	int edge_n;
	cin>>ver_n>>edge_n;

	edge_vector.clear();
	weight_vector.clear();

	edge_vector.resize(edge_n);
	weight_vector.resize(edge_n);

	for(int i = 0; i < edge_n; ++i) {
	    int sv, ev, weight;
	    cin>>sv>>ev>>weight;
	    edge_vector[i] = make_pair(sv,ev);
	    weight_vector[i] = weight;
	}

	Graph g(edge_vector.begin(), edge_vector.end(), weight_vector.begin(), ver_n);

	property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
	std::vector < Edge > spanning_tree;

	kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

	Vertex s = vertex(0,g);
	std::vector<Vertex> p(num_vertices(g));
	std::vector<int> d(num_vertices(g));
	dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));

	int sum = 0;
	for(std::vector<Edge>::const_iterator it = spanning_tree.begin();
	    it != spanning_tree.end(); ++it) {
	    sum += weight[*it];
	}

	vector<int>::iterator max = max_element(d.begin(), d.end());

	cout<<sum<<" " <<*max<<"\n";
    }

    return 0;
}
