#include <iostream>
#include <vector>

#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/pending/indirect_cmp.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    typedef pair<int, int> E;

    typedef adjacency_list <vecS, vecS, undirectedS> Graph;
    typedef graph_traits <Graph>::edge_descriptor Edge;
    typedef graph_traits <Graph>::vertex_descriptor Vertex;

    int TC;
    cin>>TC;

    vector<E> edges;
    for(int tc = 0; tc < TC; ++tc) {
	int n,m;
	cin>>n>>m;
	edges.clear();
	edges.resize(m);
	int s0,s1;
	for(int i = 0; i < m; ++i) {
	    cin>>s0>>s1;
	    edges[i] = make_pair(s0,s1);
	}

	//corner cases eg: n < 3, graph not connected.
	if(n < 3) {
	    cout<<"no\n";
	    continue;
	}

	Graph g(edges.begin(), edges.end(), n);

	vector<int> component(num_vertices(g));
	int num = connected_components(g, &component[0]);
	if(num > 1) {
	    cout<<"no\n";
	    continue;
	}

	vector<Vertex> p(num_vertices(g));
	Vertex s = vertex(0,g);

	typedef graph_traits <Graph>::vertices_size_type Size;
	std::vector<Size> dtime(num_vertices(g));
	Size time = 0;

	boost::breadth_first_search
	    (g, s,
	     boost::visitor(boost::make_bfs_visitor
			    (std::make_pair(
				boost::record_predecessors(&p[0], boost::on_tree_edge()),
				stamp_times(&dtime[0], time, on_discover_vertex())))));

	vector<graph_traits<Graph>::vertices_size_type > discover_order(n);

	integer_range < int >range(0, n);

	copy(range.begin(), range.end(), discover_order.begin());
	sort(discover_order.begin(), discover_order.end(),
		  indirect_cmp < Size*, std::less < Size > >(&dtime[0]));

	vector<int> vs0;
	vector<int> vs1;
	vector<int> vs2;

	vector<int> colors(n,0);
	vs0.push_back(0);
	for(int i = 1 ; i<n; ++i) {
	    int ivertex = discover_order[i];
	    int parent_color = colors[p[ivertex]];
	    colors[ivertex] = (parent_color + 1) % 3;
	    if(colors[ivertex] == 0) {
		vs0.push_back(ivertex);

	    }
	    else if(colors[ivertex] == 1) {
		vs1.push_back(ivertex);

	    }
	    else if(colors[ivertex] == 2) {
		vs2.push_back(ivertex);
	    }
	}

	int size2 = vs2.size();

	if(size2 == 0) {
	    int last = *(vs1.end() - 1);
	    vs1.erase(vs1.end() - 1);
	    vs2.push_back(last);
	}

	cout<<"yes\n";
	typedef vector<int>::iterator VI;
	cout<<vs0.size() << " ";
	for(VI it = vs0.begin(); it != vs0.end(); ++it) {
	    cout<<*it<<" ";
	}
	cout<<"\n";
	cout<<vs1.size() << " ";
	for(VI it = vs1.begin(); it != vs1.end(); ++it) {
	    cout<<*it<<" ";
	}
	cout<<"\n";
	cout<<vs2.size() << " ";
	for(VI it = vs2.begin(); it != vs2.end(); ++it) {
	    cout<<*it<<" ";
	}
	cout<<"\n";
    }

    return 0;
}

