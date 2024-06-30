#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {

	int n, w;
	cin >> n >> w;
	vector<int> cups(n * 2);

	for (int i = 0; i < n * 2; i++) {
		cin >> cups[i];
	}

	sort(cups.begin(), cups.end());

	double m = min(1.0 * cups[0], 1.0 * cups[n] / 2);
	double total = 3 * m * n;

	if (total  > 1.0 *w) cout << w;
	else cout << setprecision(9) << min(total, 1.0 * w);
	return 0;
}