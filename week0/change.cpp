#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int bestResult;

int solve(int change, vector<int>& coins, unsigned int i, int result) {
    if(result >= bestResult) {
	return INT_MAX;
    }

    if(coins.size() == i)
	return INT_MAX;

    if(change == 0){
	if(result < bestResult) {
	    bestResult = result;
	}
	return result;
    }

    if(change > 0) {
	int uChange = change - coins[i];
	if(uChange >= 0) {
	    return min(solve(uChange, coins, i, result + 1),
		       solve(change, coins, i + 1, result));
	}
	else {
	    return solve(change, coins, i + 1, result);
	}
    }
    else { /** change < 0 */
	return INT_MAX;
    }
}

// typedef pair<int, int> ints_pair;

// void solveIter(int ichange, vector<int>& coins, unsigned int i, int result) {
//     deque<pair<int, ints_pair> > deck;

//     deck.push_front(make_pair(ichange, make_pair(i+1, result))); //without first coin;
//     deck.push_front(make_pair(ichange - coins[i], make_pair(i, result))); //with first coin;

//     while(!deck.empty()){
// 	pair<int,ints_pair> p = deck.front(); deck.pop_front();
// 	int change = p.first;
// 	ints_pair& ip = p.second;
// 	int j = ip.first;
// 	int result = ip.second;

// 	if(result >= bestResult)
// 	    continue;

// 	if(change == 0){
// 	    if(result < bestResult) {
// 		bestResult = result;
// 	    }
// 	}

// 	if(change > 0) {
// 	    int uChange = change - coins[j];
// 	    deck.push_front(make_pair(change, make_pair(j+1, result)));
// 	    if(uChange > 0)
// 		deck.push_front(make_pair(uChange, make_pair(j, result + 1)));
// 	}
//     }
// }

int main(int argc, char *argv[])
{
    cin.sync_with_stdio ( false );
    cout.sync_with_stdio ( false );

    int N;
    cin>>N;
    for (int i = 0; i < N; ++i)
    {
	int nCoins, mSample;
	cin>>nCoins>>mSample; assert(1 <= nCoins && nCoins <= 100);
	vector<int> coins(nCoins);

	for (int j = nCoins - 1; j >= 0; --j)
	{
	    cin>>coins[j];
	}

	for (int j = 0; j < mSample; ++j)
	{
	    int change;
	    cin>>change; assert(1 <= change && change <= 10000);
	    bestResult = INT_MAX;
	    solve(change, coins, 0, 0);
	    if(bestResult != INT_MAX) {
		cout<<bestResult<<"\n";
	    } else {
		cout<<"not possible\n";
	    }
	}
    }

    return 0;
}

