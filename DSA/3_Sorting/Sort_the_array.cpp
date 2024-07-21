/**
 * codeforce: Sort the array
 * https://codeforces.com/problemset/problem/451/B
 */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void can_sort_by_reversing_subsegment(int n, vector<int>& a) {
    int l = -1, r = -1;

    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            l = i;
            break;
        }
    }

    if (l == -1) {
        cout << "yes\n";
        cout << 1 << " " << 1 << endl;
        return;
    }

    for (int i = n - 1; i > 0; --i) {
        if (a[i] < a[i - 1]) {
            r = i;
            break;
        }
    }

    reverse(a.begin() + l, a.begin() + r + 1);

    bool sorted = true;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            sorted = false;
            break;
        }
    }

    if (sorted) {
        cout << "yes\n";
        cout << l + 1 << " " << r + 1 << endl;
    } else {
        cout << "no\n";
    }
}

int can_sort(int n; vector<int>& a)
{
    int n;
    cin >> n;
    vector<int> a(n), sorted_a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sorted-a = a[i];
    }

    sort(sorted_a.begin(), sorted_a.end());
    int l  = 0, r = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] != sorted_a[i])
        {
            l = i;
            break;
        }
    }

    for (int i = n-1; i >=0 ; i--)
    {
        if (a[i] != sorted_a[i])
        {
            r = i;
            break;
        }
    }

    reverse(a.begin() + l, a.begin() + r  + 1);
    return a != sorted_a;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    can_sort_by_reversing_subsegment(n, a);

    return 0;
}
