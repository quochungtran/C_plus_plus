/**
 * codeforces: Devu, the Dumb Guy
 * https://codeforces.com/problemset/problem/439/B
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long selfLearning(vector<int>& subjects, int x)
{
    sort(subjects.begin(), subjects.end());
    long long min_time = 0;

    for (int sub : subjects)
    {
        min_time += 1LL * sub * x;

        if (x > 1)
        {
            x--;
        }
    }

    return min_time;
}


int main()
{
    int n, x; 
    cin >> n >> x;
    vector<int> subjects(n);

    for (int i = 0; i < n; i++)
    {
        cin >> subjects[i];
    }

    long long res = selfLearning(subjects, x);
    cout << res;

    return 0;
}
