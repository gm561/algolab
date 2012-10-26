#include <iostream>
h#include <vector>
#include <climits>

using namespace std;

struct Floor {
    int weight;
    int capacity;
    int cost;

    Floor() {}

    Floor(int w, int cap, int co) : weight(w), capacity(cap), cost(co) {}

};

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin>>TC;

    for(int tc = 0; tc < TC; ++tc) {
	int N; cin >> N;

	vector<Floor> floors(N);
	for(int i = 0; i < N; ++i) {
	    int weight, capacity, cost;
	    cin>>weight>>capacity>>cost;
	    Floor f(weight, capacity, cost);
	    floors[i] = f;
	}

	int min_cost = INT_MAX;
	int min_residual_capacity = 0;

	for(int i = 0; i < N; ++i) {
	    int total_weight = 0;
	    int total_cost = 0;

	    if(min_residual_capacity > floors[i].weight) {
		if(min_residual_capacity != INT_MAX) {
		    min_residual_capacity -= floors[i].weight;
		    continue;
		}
	    }

	    min_residual_capacity = INT_MAX;
	    for(int j = i; j >= 0; --j) {
		//blow the floor
		total_weight += floors[j].weight;
		if(floors[j].capacity >= total_weight ) {
		    int can_lift = floors[j].capacity - total_weight;
		    if(can_lift < min_residual_capacity) {
			min_residual_capacity = can_lift;
		    }
		    total_cost += floors[j].cost;
		}
	    }

	    if(total_cost < min_cost) {
		min_cost = total_cost;
	    }
	}

	cout<<min_cost<<"\n";
    }

    return 0;
}

