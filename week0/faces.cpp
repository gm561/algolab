#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;


int main(int argc, char *argv[])
{
    int nEdges = 0, nVertices = 0;

    while(cin>>nVertices>>nEdges) {
	vector<vector<int> > graph(nVertices);
	vector<bool> isVisited(nVertices, false);

	 int components = 0;

	for (int i = 0; i < nVertices; ++i)
	{
	    graph[i] = vector<int>();
	}

	for (int i = 0; i < nEdges; ++i)
	{
	    int v0,v1;
	    cin>>v0>>v1;

	    (graph[v0-1]).push_back(v1-1);
	    (graph[v1-1]).push_back(v0-1);
	}

	queue<int> toVisit;
	for (int i = 0; i < nVertices; ++i)
	{
	    if(isVisited[i]) continue;

	    isVisited[i] = true;
	    ++components;
	    toVisit.push(i);

	    while(!toVisit.empty()) {
		int vertex = toVisit.front();
		vector<int> edges = graph[vertex]; toVisit.pop();

		for(vector<int>::iterator it = edges.begin();
		    it != edges.end();
		    ++it)
		{
		    if(!isVisited[*it]) {
			isVisited[*it] = true;
			for(vector<int>::iterator it2 = (graph[*it]).begin();
			    it2 != (graph[*it]).end();
			    ++it2) {
			    if(!isVisited[*it2]){
				toVisit.push(*it2);
				isVisited[*it2] = true;
			    }
			}
		    }
		}
	    }
	}

	cout<<(nEdges - nVertices + 1 + components)<<"\n";
    }

    return 0;
}

