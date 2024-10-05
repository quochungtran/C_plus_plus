#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int main()
{
    int N, Q;
    int L, R;

    cin >> N;
    vector<int> a(N+1, 0), numberOfOne(N+1, 0);
    for (int i = 1; i <= N; i++) cin >> a[i];
    
    for (int i = 1; i <= N; i++)
    {
        numberOfOne[i] = numberOfOne[i-1] + a[i];
    }

    cin >> Q;
    while (Q--)
    {
        cin >> L >> R;
        int numsOne = numberOfOne[R] - numberOfOne[L-1];
        cout << numsOne % 2 << " " << (R - L + 1) - (numsOne) << "\n";
    }
    return 0;
}

using namespace std;