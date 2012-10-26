#include <iostream>

using namespace std;

 #define NOS -1

 int main(int argc, char *argv[]) {
     cin.sync_with_stdio(false);
     cout.sync_with_stdio(false);

     int test_cases;
     cin>> test_cases;

     for (int tc = 0; tc < test_cases; ++tc) {
	 int N;
	 cin>>N;

	 vector<int> solution(N, NOS);
	vector<vector<int> > board(N, vector<int> (N, EMPTY));
	 
    }


    return 0;
}
