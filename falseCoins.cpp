#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    int M;
    cin>> M;

    for (int i = 0; i < M; ++i)
    {
	int N,K;
	cin>> N >> K;

	set<int> lighterOld(N);
	set<int> heavierOld(N);

	set<int> heavierNew;
	set<int> ligherNew;

	for(int j = 0; j < N; ++j) {
	    lighterOld.insert(j);
	    heavierOld.insert(j);
	}

	for(int j = 0; j < K; ++j) {
	    int pi;
	    cin>>pi;
	    vector<int> results(2*pi);
	    for(int k = 0; k < 2*pi; ++k) {
		cin>>results[k];
	    }
	    char sign;
	    cin>>sign;
	    if(sign == '='){
		for(int k = 0; k <2*pi; ++k) {
		    lighterOld.erase(ligherOld.find(results[k]));
		    heavierOld.erase(heavierOld.find(results[k]));
		}
	    }
	    else if(sign == '>') {
		for(int k = 0; k < pi; ++k) {
		    set<int>::iterator it = heavierOld.find(k);
		    if(it != heavierOld.end()){
			heavierNew.insert(k);
		    }
		}

		for(int k = pi; k < 2*pi; ++k) {
		    set<int>::iterator it = ligherOld.find(k);
		    if(it != ligherOld.end()) {
			ligherNew.insert(k);
		    }
		}
	    }
	    else if(sign == '<') {
		for(int k = 0; k < pi; ++k) {
		    set<int>::iterator it = ligherOld.find(k);
		    if(it != ligherOld.end()) {
			ligherNew.insert(k);
		    }
		}

		for(int k = pi; k < 2*pi; ++k) {
		    set<int>::iterator it = heavierOld.find(k);
		    if(it != heavierOld.end()){
			heavierNew.insert(k);
		    }
		}
	    }

	    ligherOld.swap(ligherNew);
	    heavierOld.swap(heavierNew);

	    ligherNew.clear();
	    heavierNew.clear();
	}

	bool isHeavier = (heavierOld.size() == 1);
	bool isLighter = (ligherOld.size() == 1);

	if(isHeavier ^ isLighter) {
	    if(isHeavier) {
		cout<<*(heavierOld.begin())<<"\n";
	    }
	    else {
		cout<<*(isLighter.begin())<<"\n";
	    }
	}
	else {
	    cout<<"0\n";
	}
    }

    return 0;
}
