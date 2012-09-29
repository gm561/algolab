#include <iostream>
#include <cassert>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void generate_changes(vector<int>& number_of_coins, vector<int>& coins, int max, int min);

int main(int argc, char *argv[])
{
    int N;
    cin >> N; assert(N >= 0);

    for (int i = 0; i < N; ++i)
    {
	int ci, mi;
	cin>>ci>>mi; assert(ci >= 1 && ci <= 100);

	vector<int> coins(ci);
	for(int j = 0; j < ci; ++j) {
	    cin>>coins[j];
	}

	vector<int> changes(mi);
	for(int j = 0; j < mi; ++j) {
	    cin >> changes[j];
	}

	int max_change = *(max_element(changes.begin(), changes.end()));
	int min_change = *(min_element(changes.begin(), changes.end()));
	assert(max_change >= min_change);

	vector<int> number_of_coins(max_change + 1, INT_MAX); // take 0 as init solution;
	generate_changes(number_of_coins, coins, max_change, min_change);

	for(vector<int>::iterator it = changes.begin(); it != changes.end(); ++it) {
	    int value = number_of_coins[*it];
	    if(value == INT_MAX || value == 0)
		cout<<"not possible\n";
	    else {
		cout<<value<<"\n";
	    }
	}
    }
    return 0;
}

void generate_changes(vector<int>& number_of_coins, vector<int>& coins, int max, int min) {
    number_of_coins[0] = 0;
    int best_result;
    int temp_result;
    int nSubsolution;

    for(int i = coins[0]; i <= max; ++i) {
	best_result = INT_MAX;
	for(vector<int>::iterator it = coins.begin(); it != coins.end(); ++it) {
	    nSubsolution = i - *it;
	    if(nSubsolution >= 0) {
//		cout<<nSubsolution<<" "<<number_of_coins[nSubsolution] <<endl;
		temp_result = number_of_coins[nSubsolution];
		if(temp_result < (best_result-1)) {
		    best_result = temp_result + 1;
		}
	    }
	}
	number_of_coins[i] = best_result;
//	cout<<"Best result for: "<<i<<" "<<number_of_coins[i]<<endl;
    }
}

