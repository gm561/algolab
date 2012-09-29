#include <iostream>
#include <cassert>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    int n,m;
    cin>>n;

    for (int i = 0; i < n; ++i)
    {
	cin>>m; assert(m>=0 && m <= 10);
	double sum = 0;
	for (int j = 0; j < m; ++j)
	{
	    double f;
	    cin>>f;
	    sum += f;
	}
	cout<<setprecision(16)<<sum<<"\n";
    }

    return 0;
}
