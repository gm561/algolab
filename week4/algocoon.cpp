#include <iostream>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/connected_components.hpp>

using namespace std;
using namespace boost;

typedef boost::adjacency_list_traits <boost::vecS, boost::vecS, boost::directedS > Traits;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS,
		       no_property,
		       property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					 property<edge_reverse_t, Traits::edge_descriptor> > >
		       > Graph;

typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;


int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin>>TC;
    for(int tc = 0; tc < TC; ++tc) {
	int V; int E;
	cin>>V>>E;

	Graph g(V);

	property_map<Graph, edge_capacity_t>::type capacity = get(edge_capacity, g);
	property_map<Graph, edge_reverse_t>::type reverse_edges = get(edge_reverse, g);

	property_map < Graph, edge_residual_capacity_t >::type
	    residual_capacity = get(edge_residual_capacity, g);

	vector<int> degres(V,0);
	for(int i = 0; i < E; ++i) {
	    int u,v; cin>>u>>v;
	    int w; cin>>w;

	    degres[u] += w;
	    degres[v] += w;

	    bool result; Edge edge, reverse;

	    tie(edge, result) = add_edge(u,v,g);
	    tie(reverse,result) = add_edge(v,u,g);

	    reverse_edges(edge) = reverse;
	    reverse_edges(reverse) = edge;

	    capacity[edge] = w;
	    capacity[reverse] = 0;

	    Edge edge0, reverse0;
	    tie(edge0, result) = add_edge(v,u,g);
	    tie(reverse0,result) = add_edge(u,v,g);

	    reverse_edges(edge0) = reverse0;
	    reverse_edges(reverse0) = edge0;

	    capacity[edge0] = w;
	    capacity[reverse0] = 0;
	}

	int max_i = 0, min_i = 0;
	for(int i = 0; i < V ;++i) {
	    int d = degres[i];

	    if(d > degres[max_i]) {
		max_i = i;
	    }

	    if(d < degres[min_i]) {
		min_i = i;
	    }
	}

	Vertex s(min_i);
	Vertex t(max_i);

	long min_flow = push_relabel_max_flow(g, s, t);
	Vertex min_target = t;

	for(int i = 1; i < V; ++i) {
	    if(i == min_i)
		continue;

	    Vertex tp(i);
	    long flow = push_relabel_max_flow(g, s, tp);
	    if(min_flow > flow) {
		min_flow = flow;
		t = tp;
	    }
	}

	min_flow = push_relabel_max_flow(g, s, t);

	// cerr<<"Source " << min_i<<" Sink "<<max_i <<"\n";
	// cerr<< min_flow << "\n";

	typedef adjacency_list<vecS, vecS, bidirectionalS> Graph_bid;
	Graph_bid g_bid(V);

	graph_traits<Graph>::edge_iterator ei, ei_end;
	for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
	    // if(capacity[*ei] > 0 && residual_capacity[*ei] == 0) {
	    // 	std::cout << "(" << source(*ei, g)
	    // 		  << "," << target(*ei, g) << ") "<<endl;
	    // }

	    if(capacity[*ei] > 0 && residual_capacity[*ei] > 0){
		add_edge(source(*ei, g), target(*ei,g), g_bid);
	    }
	}

	cout<<min_flow<<"\n";
	vector<int> my_v;

	std::vector<int> component(num_vertices(g_bid));
	int num = connected_components(g_bid, &component[0]);

	int source_component = component[min_i];
	for (int j = 0; j != component.size(); ++j)
	    if(component[j] == source_component) {
		// cout << "Vertex " << j <<" is in component " << component[j] << endl;
		my_v.push_back(j);
	    }

	cout<<my_v.size() << " ";
	for(int i = 0; i < my_v.size(); ++i) {
	    cout<<my_v[i]<<" ";
	}
	cout<<"\n";
    }

    return 0;
}
