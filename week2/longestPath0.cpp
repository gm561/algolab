#include <iostream>
#include <vector>

using namespace std;

#define SIZE(x) (int) x.size()
#define UNKNOWN -1

int dfs(vector<vector<pair<int,int> > >& tree, int n, int root) {
    int value = 0;

    for(int i = 0; i <  SIZE(tree[n]); ++i) {
	if((tree[n][i]).first == root)
	    continue;

	int cvalue = (tree[n][i]).second;
	if(cvalue == UNKNOWN){
	    cvalue  = dfs(tree, (tree[n][i].first), n);
	    tree[n][i] = make_pair((tree[n][i]).first, cvalue);
	}

	if(cvalue > value)
	    value = cvalue;
    }

    return value + 1;
}

int main(int argc, char *argv[])
{
    int N;
    cin>>N;
    for (int ti = 0; ti < N; ++ti)
    {
	int nvertex;
	cin>>nvertex;

	vector<vector<pair<int, int> > > tree(nvertex);

	int l1,l2;
	for(int i = 0; i < nvertex-1 ; ++i) {
	    cin>>l1>>l2;
	    tree[l1].push_back(make_pair(l2, UNKNOWN));
	    tree[l2].push_back(make_pair(l1, UNKNOWN));
	}

	int max0 = 0;
	int max1 = 0;
	int value = 0;

	int l_path = 0;
	for(int i = 0; i < nvertex - 1; ++i) {
	    max0 = 0;
	    max1 = 0;
	    value = 0;

	    for(int j = 0; j < SIZE(tree[i]); ++j) {
		value = dfs(tree, tree[i][j].first, i);
		if(value > max0) {
		    max1 = max0;
		    max0 = value;
		}
		else if(value > max1) {
		    max1 = value;
		}
		if(max1+max0 > l_path) {
		    l_path = max1 + max0;
		}
	    }
	}

	cout<<l_path + 1<<"\n";
    }

    return 0;
}

