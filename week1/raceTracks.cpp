#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <set>

typedef std::pair<int,int> point;
typedef std::pair<int,int> velocity;

using namespace std;

int bfs_search(const set<point>& obstacles,
	       const point& start_point,
	       const point& end_point,
	       int X, int Y);

int main(int argc, char *argv[])
{

    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int N;
    cin>> N;

    while(N--) {
	assert(N>=0);

	//board size
	int X,Y;
	cin>>X>>Y;

	//reading start and end points
	int x,y;
	cin>>x>>y;
	point start_point(x,y);
	cin>>x>>y;
	point end_point(x,y);

	set<point> obstacles;
	int obst_count;
	int obst_Xs, obst_Ys, obst_Xe, obst_Ye;
	cin>>obst_count;

	for(int i = 0 ; i < obst_count; ++i) {
	    cin>>obst_Xs>>obst_Ys>>obst_Xe>>obst_Ye;

	    if(obst_Xs > obst_Xe) {
		swap(obst_Xs, obst_Xe);
	    }

	    if(obst_Ys > obst_Ye) {
		swap(obst_Ys, obst_Ye);
	    }

	    assert(obst_Xs <= obst_Xe && obst_Ys <= obst_Ye);

	    for(int j = obst_Xs; j <= obst_Xe; ++j) {
		for (int k = obst_Ys; k <= obst_Ye; ++k) {
		    obstacles.insert(point(j,k));
		}
	    }
	}

	int value = dfs_search(obstacles, start_point, end_point, X, Y);
	if(value < 0) {
	    cout<<"No solution.\n";
	}
	else {
	    cout<<"Optimal solution takes "<<value<<" hops.\n";
	}
    }

    return 0;
}

struct Node {
    point p;
    velocity v;
    int hops;

    Node(const point p_ = make_pair(0,0), const velocity v_ = make_pair(0,0)) {
	p = p_;
	v = v_;
	hops = -1;
    }

    Node(const Node& node) {
	p = node.p;
	v = node.v;
	hops = node.hops;
    }

    bool operator==(const Node& n) const {
	return p.first == n.p.first &&
	    p.second  == n.p.second &&
	    v.first == n.p.first &&
	    v.second == n.p.second;
    }

    bool operator<(const Node& n) const {
	if(p.first < n.p.first)
	    return true;
	if(p.first > n.p.first)
	    return false;

	if(p.second < n.p.second)
	    return true;
	if(p.second > n.p.second)
	    return false;

	if(v.first < n.v.first)
	    return true;
	if(v.first > n.v.first)
	    return false;

	if(v.second < n.v.second)
	    return true;
	if(v.second > n.v.second)
	    return false;

	return false;
    }
};


void generate_nodes(Node& node, vector<Node>& nodes, int X, int Y){

    //  cout<<"From node (" << node.p.first << "," << node.p.second <<")" <<"velocity " << node.v.first <<"," << node.v.second << endl;

    for(int i = -1 ; i <=1 ; ++i) {
	for(int j = -1; j<= 1; ++j) {
	    velocity v;
	    v.first = node.v.first + i;
	    v.second = node.v.second + j;

	    if(!(v.first >= -3 &&
		 v.first <= 3 &&
		 v.second >= -3 &&
		 v.second <= 3)) {
		continue;
	    }

	    point p;
	    p.first = node.p.first + v.first;
	    p.second = node.p.second + v.second;

	    Node n(p,v);

	    if(!(
		   n.p.first >= 0 &&
		   n.p.first <=  X-1 &&
		   n.p.second >= 0 &&
		   n.p.second <= Y-1))
	    {
		continue;
	    }

//	    cout<<"Create node ("<< n.p.first << "," << n.p.second << ") "<<endl;

	    nodes.push_back(n);
	}
    }
}

int bfs_search(const set<point>& obstacles,
	       const point& start_point,
	       const point& end_point,
	       int X, int Y) {

    bool isSolveable = false;
    set<Node> visited;
    queue<Node> q;
    Node sp(start_point, velocity(0,0));
    if(start_point == end_point)
	return 0;

    if(obstacles.end() != obstacles.find(end_point))
	return -1;

    sp.hops = 0;

    q.push(sp);
    visited.insert(sp);
    int hops = -1;
    while(!q.empty() && !isSolveable) {
	Node node = q.front();
	q.pop();

	vector<Node> nodes;
	//	cout<<"("<< node.p.first << "," << node.p.second << ") (" << node.v.first <<
	//  "," << node.v.second<<")"<<endl;

	generate_nodes(node, nodes, X, Y);

	for(vector<Node>::iterator it = nodes.begin();
	    it != nodes.end();
	    ++it) {

//	     cout<<"N: ("<<(*it).p.first << "," <<(*it).p.second << ") (" <<(*it).v.first <<"," <<(*it).v.second<<")"<<endl;

	    if(obstacles.end() != obstacles.find((*it).p)) {
		continue;
	    }

	    if((*it).p.first == end_point.first &&
	       (*it).p.second == end_point.second) {
		isSolveable = true;
		hops = node.hops + 1;
		break;
	    }

	    if(visited.find(*it) == visited.end()) {
		(*it).hops = node.hops + 1;
		q.push(*it);
		visited.insert(*it);
//		cout<<"Visited size " << visited.size();
	    }
	}
    }

    return hops;
}

