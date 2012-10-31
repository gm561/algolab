#include <iostream>
#include <vector>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

#define SIZE(x) (int)x.size()

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;

static const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

int main(int argc, char *argv[])
{
    int TC; cin >> TC;

    for(int tc = 0; tc < TC; ++tc) {
	int g, s, l;
	cin>>g>>s>>l;

	vector<Vertex> matches(g+s);
	vector<int> sats(s);
	vector<int> globs(g);

	Graph graph(g+s);
	//read first the ground station then satellite
	for(int i = 0; i < l; ++i) {
	    int u,v;  cin>>u>>v;
	    add_edge(u, v+g ,graph);
	}

	edmonds_maximum_cardinality_matching(graph, &matches[0]);

	vector<int> unmatched;
	for(int i = 0; i < SIZE(matches); ++i) {
	    if(matches[i] == NULL_VERTEX) {
		unmatched.push_back(i);
	    }
	}

	cout<<"Matching size "<< (s + g  - SIZE(unmatched))/2.0<<endl;

	//then |g| == |s| perfect bipartie graph
	if(unmatched.empty()) {
	    cout<<g<<" "<<0<<"\n";
	    for(int i = 0; i < g; ++i) { assert(g == s);
		cout<<i <<" ";
	    }
	    cout<<"\n";
	    continue;
	}

	vector<int> visited(g+s,0);

	//put all unmatched verticies to the queue
	queue<pair<int,bool> > q;
	for(int i = 0; i < SIZE(unmatched); ++i) {
	    q.push(make_pair(unmatched[i], false));
	}

	typename graph_traits<Graph>::adjacency_iterator ai;
	typename graph_traits<Graph>::adjacency_iterator ai_end;

	vector<int> min_set;

	while(!q.empty()) {
	    pair<int, bool> v = q.front(); q.pop();

	    if(visited[v.first] == 0) {
		visited[v.first] = 1;
		for (tie(ai, ai_end) = adjacent_vertices(v.first, graph);
		     ai != ai_end; ++ai) {
		    if(visited[*ai] == 0) {
			visited[*ai] = 1;
			if(v.second == false) {
			    min_set.push_back(*ai);
			}

			q.push(make_pair(*ai, !v.second));
		    }
		}
	    }
	}

	for(int i = 0; i < SIZE(visited); ++i) {
	    cout<<visited[i]<<endl;
	}

	int gmin = 0, smin = 0;
	for(int i = 0; i < SIZE(min_set); ++i) {
	    if(min_set[i] > g) {
		++smin;
	    }
	    else {
		++gmin;
	    }
	}

	cout<<gmin<< " " << smin<<"\n";
	for(int i = 0; i < SIZE(min_set); ++i) {
	    cout<<min_set[i]<< " ";
	}

	cout<<"\n";
    }

    return 0;
}
