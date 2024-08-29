/*
* Link : https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1167
* Complexity: O(N∗log(N))  N: number of trees
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	// freopen("INPUT.INP", "rt", stdin);
	string s;
	set<pair<string, int> > myset;
	set< pair<string, int> >::iterator it;
	int test;
	cin >> test;
	getline(cin, s);
	getline(cin, s);
	while (test--)
	{
		int count = 0;
		while (getline(cin, s))
		{
			if (s.size() < 1)
				break;
			count++;
			it = myset.lower_bound(make_pair(s, 0));
			if (it == myset.end() || it->first != s)
				myset.insert(make_pair(s, 1));
			else
			{
				int number = (it->second) + 1;
				myset.erase(it);
				myset.insert(make_pair(s, number));
			}
		}
		
		for (it = myset.begin(); it != myset.end(); it++)
		{
			cout << (it->first).c_str() << " ";
			cout << fixed << setprecision(4) << (100.0*(it->second) / count) << endl;
		}
		if (test)
			cout << endl;
		myset.clear();
	}
	
	return 0;
}