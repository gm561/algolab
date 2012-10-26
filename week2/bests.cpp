#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define NOS -1
#define EMPTY 0
#define TAKEN 1
#define SIZE(X) ((int) X.size())


inline void mark_fields(int x, int y, vector<vector<int> >& board, int N, int value = 1) {
    //mark horizonal
    for (int i = x; i < N; ++i) {
	board[i][y] += value;
    }
    //mark diagonal
    for (int i = x; i < N; ++i) {
	if( (i + y - x) < N && (i + y - x) >= 0) {
	    board[i][i + y - x] += value;
	}

	if( (- i + y + x) < N && (-i + y + x) >= 0) {
	    board[i][-i + y + x] += value;
	}
    }
}

bool dfs(int column, vector<int>& solution, vector<vector<int> >& board, const int N) {
    if(column == N) {
	return true;
    }

    bool result = false;
    for(int i = 0; i < N; ++i) {
	if(board[column][i] == EMPTY) {
	    solution[column] = i;
	    mark_fields(column, i, board, N);
	    result = dfs(column + 1, solution, board, N);
	    if(result) {
		return true;
	    }

	    mark_fields(column, i, board, N, -1);
	}
    }

    return result;
}

inline bool checkSolution(const vector<int>& solution) {
    for(int j = 0; j < SIZE(solution); ++j) {
	int pos = solution[j];
	for (int i = 0; i < SIZE(solution); ++i) {
	    if(i == j )
		continue;

	    //horizonal
	    assert(pos != solution[i]);

	    //diagonal
	    assert(pos - j + i != solution[i]);
	    assert(pos + j - i != solution[i]);
	}
    }

    return true;
}


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
	bool result = dfs(0, solution, board, N);

	if(result) {
	    assert(checkSolution(solution));
	    for(int i = 0; i < N - 1; ++i) {
		cout<<solution[i] + 1<< " ";
	    }
	    cout<<solution[N-1] + 1<< "\n";
	}
	else {
	    cout<<"Not possible\n";
	}
    }

    return 0;
}
