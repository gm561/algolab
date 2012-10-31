#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>


using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    typedef std::pair<int, int> E;
    typedef adjacency_list<vecS, vecS, undirectedS,
			   no_property, no_property> Graph;

    int TC;
    cin>>TC;

    for(int tc = 0; tc < TC; ++tc) {
	int n,m;
	cin>>n>>m;
	vector<E> edges(m + n);

	for(int i = 0; i < m; ++i) {
	    int f0,f1;
	    cin>>f0>>f1;

	    edges[i] = make_pair(f0,f1);
	}

	for(int i = 0; i < n; ++i) {
	    edges[i + m] = make_pair(i, n);
	}

	Graph g(edges.begin(), edges.end(), n + 1);

	bool is_planar = boyer_myrvold_planarity_test(g);
	is_planar ? cout<<"yes\n" : cout<<"no\n";
    }

    return 0;
}

