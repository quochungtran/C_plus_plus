// Link of the problem: 
// https://www.hackerearth.com/practice/data-structures/trees/binary-search-tree/practice-problems/algorithm/distinct-count/

#include <iostream>
#include <set>
using namespace std;


// Complexity O(T∗N∗logN) T: number of test, N is number of elements

int main() {
	int T, N, X, temp;
	set<int> s;
	cin >> T;

	while (T--) {
		s.clear();
		cin >> N >> X;

		for (int i = 0; i < N; i++) {
			cin >> temp;
			s.insert(temp); // log(N)
		}

		int diff = s.size();

		if (diff == X) {
			cout << "Good" << endl;
		}
		else {
			cout << (diff < X ? "Bad" : "Average") << endl;
		}
	}
	return 0;
}