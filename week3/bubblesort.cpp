#include <iostream>
#include <vector>

#include <boost/assign/std/vector.hpp>

using namespace std;
using namespace boost::assign;

template<typename It>
void bubblesort(It begin, It end) {
    for(It it0 = begin; it0 != end; ++it0) {
	for(It it1 = it0, it2 = it1++; it2 != end; ++it1, ++it2) {
            cout<<"Swap"<<endl;
            cout<<*it2 << *it1 <<endl;
	    swap(*it2,*it1);
            cout<<*it2 << *it1 <<endl;
	}
    }
}


int main(int argc, char *argv[])
{
    vector<int> ints;
    ints += 1,3,5,1,2,9;
    bubblesort(ints.begin(), ints.end());

    for(vector<int>::iterator it = ints.begin(); it != ints.end(); ++it) {
         cout<<*it;
    }

    return 0;
}
