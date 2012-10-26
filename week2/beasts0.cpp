#include <iostream>
#include <vector>
#include <cassert>

#define EMPTY 0
#define TAKEN 1
#define SIZE(X) ((int) X.size())

using namespace std;

inline int mark_fields(int x, int y, vector<vector<int> >& board, int N) {
    int number_marks = 0;

    //mark horizonal
    for (int i = x; i < N; ++i) {
	if(board[i][y] != TAKEN) {
	    board[i][y] = TAKEN;
	    ++number_marks;
	}
    }

    //mark diagonal
    for (int i = x; i < N; ++i) {
//	cout<<"H - (" << i << "," << i + y - x << ")"<<endl;
	if( (i + y - x) < N && (i + y - x) >= 0) {
	    if(board[i][i + y - x] != TAKEN) {
		board[i][i + y - x] = TAKEN;
		++number_marks;
	    }
	}

//	cout<<"V - (" << i << "," << - i + y + x << ")"<<endl;
	if( (- i + y + x) < N && (-i + y + x) >= 0) {
	    if(board[i][i + y - x] != TAKEN) {
		board[i][-i + y + x] = TAKEN;
		++number_marks;
	    }
	}
    }

    return number_marks;
}

inline bool checkSolution(const vector<int>& solution) {
    for(int j = 0; j < SIZE(solution); ++j) {
	int pos = solution[j];
	for (int i = 0; i < SIZE(solution); ++i) {
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

	bool solveable = true;

	vector<vector<int> > board(N, vector<int> (N, EMPTY));
	vector<int> solution(N);

	for(int i = 0; i < N; ++i) {
	    if(!solveable) break;
	    solveable = false;
	    int marked = 0;
	    int min = 999999;
	    int best = -1;
	    for(int j = 0; j < N; ++j) {
		if(board[i][j] == EMPTY) {
		    board[i][j] = TAKEN;
		    marked = mark_fields(i, j, board, N);

		    if(marked < min) {
			min = marked;
			best = j;
		    }

		    solveable = true;
		}
	    }

	    solution[i] = best;
	    assert(checkSolution);
	}

	if(solveable) {
	    for(int i = 0 ; i < N - 1; ++i) {
		cout << solution[i] + 1 << " ";
	    }
	    cout<<solution[N-1] + 1<< "\n";
	}
	else {
	    cout<<"Not possible\n";
	}
    }

    return 0;
}
