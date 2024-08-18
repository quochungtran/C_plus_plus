#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T, N, M;
    long long x;
    cin >> T;
    set<long long> s;
    while(T--){
        cin >> N >> M;
        s.clear();
        for (int i = 0; i < N; i++)
        {
            cin >> x;
            s.insert(x);
        }

        for (int i = 0; i < M; i++)
        {
            cin >> x;
            if (s.find(x) != s.end())
            {
                cout << "YES" << "\n";
            }
            else
            {
                cout << "NO" << "\n";
              	s.insert(x);
            }
        }
    }
    return 0;
}