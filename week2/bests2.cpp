#include <iostream>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define NOS -1
#define EMPTY 0
#define TAKEN 1
#define SIZE(X) ((int) X.size())


inline void mark_fields(int x, int y, vector<vector<int> >& board, int N, int value = 1) {
    //mark horizonal
    for (int i = 0; i < N; ++i) {
	if(i != x)
	    board[i][y] += value;
    }

    //mark diagonal
    for (int i = 0; i < N; ++i) {
	if( (i + y - x) < N && (i + y - x) >= 0) {
	    if(i != x)
		board[i][i + y - x] += value;
	}

	if( (- i + y + x) < N && (-i + y + x) >= 0) {
	    if( i != x)
		board[i][-i + y + x] += value;
	}
    }
}

inline int find_best(vector<vector<int> >& board, const int column, const int N) {
    int best_number = 0;
    int best_value = board[column][0];

    for(int i = 0; i < N; ++i) {
	int cur_value = board[column][i];
	if(cur_value > best_value) {
	    best_value = cur_value;
	    best_number = i;

	    if(best_value == 0)
		break;
	}
    }

    return best_number;
}

void greedyRandomizeSolution(vector<int>& solution, vector<vector<int> >& board, const int N) {
    srand ( time(NULL) );
    for(int i = 0; i < N; ++i) {
	int row = find_best(board, i, N);
	solution[i] = row;
	mark_fields(i, row, board, N, -1);
    }

    //we got greedy solution no improve it!
    //check correctness.
    int correct = true;
    for(int i = 0; i < N; ++i) {
	if(board[i][solution[i]] != 0){
	    correct = false;
	    break;
	}
    }

    if(correct) return;

    int worse = 0;
    int worse_index = 0;
    int random_row = 0;
    int last_worse = 0;

    // cout<<"begin"<<endl;
    do {
	assert(worse <= 0);

	// for(int i = 0; i < N - 1; ++i) {
	//     cout<<solution[i] + 1<< " ";
	// }
	// cout<<solution[N-1] + 1<< endl;

	worse = 0;
	for(int i = 0; i < N; ++i) {
	    int value = board[i][solution[i]];
	    if(value < worse) {
		worse = value;
		worse_index = i;
	    }
	}

	if(worse == 0)
	    break;

	if(last_worse == worse_index) {
	    worse_index = rand() % N;
	    random_row = rand() % N;
	}

	//find the best row
	int improve_value = board[worse_index][0];
	for(int i = 1; i < N ; ++i) {
	    int temp = board[worse_index][i];
	    if(improve_value < temp) {
		improve_value = temp;
		random_row = i;
	    }
	}

	last_worse = worse_index;

	mark_fields(worse_index, solution[worse_index], board, N, 1);
	mark_fields(worse_index, random_row, board, N, -1);
	solution[worse_index] = random_row;

	correct = true;
	for(int i = 0; i < N; ++i) {
	    if(board[i][solution[i]] != 0){
		correct = false;
		break;
	    }
	}

    } while(!correct);
	// cout<<"worse value "<< worse << " worse index: " <<worse_index<<
	//     " last worse " << last_worse<<endl;

    // cout<<"solution\n";
    // for(int i = 0; i < N - 1; ++i) {
    // 	cout<<solution[i] + 1<< " ";
    // }
    // cout<<solution[N-1] + 1<< endl;

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

	if(N == 2 || N == 3) {
	    cout<<"Impossible\n";
	    continue;
	}

	vector<int> solution(N, NOS);

	vector<vector<int> > board(N, vector<int> (N, EMPTY));

	greedyRandomizeSolution(solution, board, N);
	assert(checkSolution(solution));

	for(int i = 0; i < N - 1; ++i) {
	    cout<<solution[i] + 1<< " ";
	}

	cout<<solution[N-1] + 1<< "\n";
    }

    return 0;
}

