#include <vector>
using namespace std;

const int INF = 1e9 + 5;

int main(){
    int n;
    cin >> n;

    vector<int> L(n), R(n);

    int left = INF, right = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> L[i] >> R[i];
        left  = min(left, L[i]);
        right = max(right, R[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (left == L[i] && right == R[i])
        {
            cout << i + 1;
            return 0;
        }
    }

    cout << -1;
    return 0;
}