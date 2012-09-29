#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;
void printSets(set<int>& heavierOld, set<int>& lighterOld) {
    cout<<"sets\n";
    for(set<int>::iterator it = heavierOld.begin();
	it != heavierOld.end();
	++it) {
	cout<<*it + 1<<" ";
    }
    cout<<" || ";
    for(set<int>::iterator it = lighterOld.begin();
	it != lighterOld.end();
	++it) {
	cout<<*it + 1<<" ";
    }
    cout<<endl;

}
int main(int argc, char *argv[])
{
    int M;
    cin>> M;

    for (int i = 0; i < M; ++i)
    {
	int N,K;
	cin>> N >> K;

	set<int> lighterOld;
	set<int> heavierOld;

	set<int> heavierNew;
	set<int> ligtherNew;

	for(int j = 0; j < N; ++j) {
	    lighterOld.insert(j);
	    heavierOld.insert(j);
	}

	for(int j = 0; j < K; ++j) {
	    int pi;
	    cin>>pi;
	    vector<int> results(2*pi);
	    for(int k = 0; k < 2*pi; ++k) {
		int temp;
		cin>>temp;
		results[k] = temp - 1;
	    }

	    bool toSwap = false;

	    char sign;
	    cin>>sign;;

	    if(sign == '=') {
		toSwap = true;
	    	for(int k = 0; k <2*pi; ++k) {
		    set<int>::iterator it0 = lighterOld.find(results[k]);
		    if(it0 != lighterOld.end())
			lighterOld.erase(it0);

		    it0 = heavierOld.find(results[k]);
		    if(it0 != heavierOld.end())
			heavierOld.erase(it0);
	    	}
	    }
	    else if(sign == '>') {
	    	for(int k = 0; k < pi; ++k) {
	    	    set<int>::iterator it = heavierOld.find(results[k]);
	    	    if(it != heavierOld.end()){
	    		heavierNew.insert(results[k]);
	    	    }
	    	}
	    	for(int k = pi; k < 2*pi; ++k) {
	    	    set<int>::iterator it = lighterOld.find(results[k]);
	    	    if(it != lighterOld.end()) {
	    		ligtherNew.insert(results[k]);
	    	    }
	    	}
	    }
	    else if(sign == '<') {
	    	for(int k = 0; k < pi; ++k) {
	    	    set<int>::iterator it = lighterOld.find(results[k]);
	    	    if(it != lighterOld.end()) {
	    		ligtherNew.insert(results[k]);
	    	    }
	    	}

	     	for(int k = pi; k < 2*pi; ++k) {
	     	    set<int>::iterator it = heavierOld.find(results[k]);
	     	    if(it != heavierOld.end()){
	     		heavierNew.insert(results[k]);
	     	    }
	     	}
	    }

	    if(!toSwap){
		lighterOld.swap(ligtherNew);
		heavierOld.swap(heavierNew);
	    }

	    ligtherNew.clear();
	    heavierNew.clear();

	}

	bool isHeavier = (heavierOld.size() == 1);
	bool isLighter = (lighterOld.size() == 1);

	if(isHeavier ^ isLighter) {
	    if(isHeavier) {
		cout<<*(heavierOld.begin()) + 1<<"\n";
	    }
	    else {
		cout<<*(lighterOld.begin()) + 1<<"\n";
	    }
	}
	else if((isHeavier && isLighter) &&
		(*heavierOld.begin() == *lighterOld.begin())){
	    cout<<*heavierOld.begin() + 1<<endl;
	} else {
	    cout<<"0\n";
	}
    }

    return 0;
}
