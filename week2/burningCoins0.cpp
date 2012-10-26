#include<iostream>
#include<vector>

using namespace std;

typedef vector<int>::iterator VI;

int burning_coins(VI s, VI e) {
    if(s == e) {
	return *s;
    }

    int s0;
    int s1;
    int s2;
    int s3;

    if(s+1 == e)
	return max(*s,*e);

    s0 = burning_coins(s+2, e) + *s;

    int tmp = burning_coins(s+1,e-1);
    s1 = tmp + *s;
    s2 = tmp + *e;

    s3 = burning_coins(s, e-2) + *e;

    return max(min(s0,s1), min(s2,s3));
}

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC;
    cin>>TC;

    for(int tc = 0 ; tc <  TC; ++tc) {
	int coin_number;
	cin>>coin_number;
	vector<int> coins(coin_number);

	for(int i = 0 ; i < coin_number; ++i) {
	    cin>>coins[i];
	}

	int s0 = burning_coins(coins.begin(), coins.begin() + coin_number - 1);
	cout<<s0<<"\n";
    }

    return 0;
}

