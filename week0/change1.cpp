#include <iostream>
#include <cassert>
#include <vector>


using namespace std;

bool solve(int change, vector<int>& coins, vector<int>& result, unsigned int i ) {

    if(coins[i] <= 0) {
	return false;
    }

    int amount = change/coins[i]; assert(change - amount*coins[i] >= 0);
//    cout<<"Amount "<<amount<<" coin: "<< coins[i] <<" Change " <<change - amount*coins[i]<<"\n";

    if(change - amount*coins[i] == 0){
	result[i] = amount;
	return true;
    }
    else if(amount > 0) {
	for(int j = amount; j >= 0; --j) {
	    bool solvable = solve(change - j*coins[i], coins, result, i+1);
	    if(solvable) {
		result[i] = j;
		return true;
	    }
	}
    }

    if(coins.size() > i + 1) {
	return solve(change, coins, result, i+1);
    }

    return false;
}

int main(int argc, char *argv[])
{
    int N; assert(N >= 0);
    cin>>N;

    for (int i = 0; i < N; ++i)
    {
	int ci,mi;
	cin>>ci>>mi; assert(1 <= ci && ci <= 100);
	vector<int> coins(ci);

	for (int j = ci-1; j >=0; --j)
	{
	    cin>>coins[j];
	}

	bool solvable = false;
	int change;

	for(int j = 0; j < mi; ++j) {
	    vector<int> result(ci,0);

	    cin>>change;
	    solvable = solve(change, coins, result, 0);

	    if(solvable) {
		int amount = 0;
		for (vector<int>::iterator it = result.begin(); it != result.end(); ++it){
		    if(*it > 0) amount += (*it);
		}
		cout<<amount<<"\n";
	    } else {
		cout<<"not possible\n";
	    }
	}
    }

    return 0;
}


