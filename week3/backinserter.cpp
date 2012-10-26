// back_inserter example
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main () {
  vector<int> firstvector, secondvector;
  for (int i=1; i<=5; i++)
  { firstvector.push_back(i); secondvector.push_back(i*10); }

  copy (secondvector.begin(),secondvector.end(), back_inserter(firstvector));

  vector<int>::iterator it;
  for ( it = firstvector.begin(); it!= firstvector.end(); ++it )
	  cout << *it << " ";
  cout << endl;

  return 0;
}

