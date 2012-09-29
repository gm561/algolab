#include <iostream>
#include <cassert>
#include <climits>

using namespace std;

int main(int argc, char *argv[])
{
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
	int l,m,n;
	cin>>l>>m>>n; assert(m <= n);

	int bestM = 0, bestN = 0, bestRest = INT_MAX;

	for(int j = l/n; j >= 0; --j)
	{
	    int rest = l - n*j; assert(rest >= 0);
	    int numberM = rest/m; assert(l - n*j - numberM*m >= 0);
	    int diff = l - (n*j + numberM*m);
	    if( diff == 0)
	    {
		bestM = numberM;
		bestN = j;
		bestRest = 0;
		goto solution;
	    }

	    if(bestRest > diff) {
		bestRest = diff;
		bestM = numberM;
		bestN = j;
	    }
	}
    solution:
	cout<<bestM<<" "<<bestN<<" "<<bestRest<<"\n";
    }

    return 0;
}
