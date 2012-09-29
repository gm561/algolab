
bool solve(const int change, const vector<int>& coins, int& result, unsigned int i) {
    int value = coins[i];

    if(change - value == 0) {
	return true;
    }

    if(change - value < 0) {
	++i;
	if(i == coins.size()) return false;

	return solve(change, coins, result, i);
    } else {
	solve(change-value, coins, result, i);
	++result;

	return true;
    }
}


inline int solveIter(const int change, vector<int>& coins) {
    deque<pair<int, v_it> > changeDeque;

    int result = 0;
    v_it it = coins.begin();

    changeDeque.push_front(make_pair(change, it));

    while(!changeDeque.empty()) {
	pair<int, v_it> p_change = changeDeque.front(); changeDeque.pop_front();
	int change0 = p_change.first;
	v_it it = p_change.second;

	result++;

	if(change0 - *it > 0 && change0 - *it < change0) {
	    if(it + 1 != coins.end())
		changeDeque.push_front(make_pair(change0, it + 1));
	    changeDeque.push_front(make_pair(change0 - *it, it));
	}
	else if(change0 - *it == 0) {
	    return result;
	}
	else {
	    ++it;
	    result--;
	    if(it != coins.end()) {
		if(it + 1 != coins.end())
		    changeDeque.push_front(make_pair(change0, it + 1));
		changeDeque.push_front(make_pair(change0, it));
	    }
	}
    }

    return -1;
}
