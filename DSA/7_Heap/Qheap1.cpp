/**
 * 
 * Complexity is O(QlogN)
 */


#include <iostream>
#include <queue>
#include <vector>

#define MAX 100000
using namespace std;
#include<queue>


int main() {
    int Q, u, v;
    cin >> Q;

    priority_queue<long long, vector<long long>, greater<long long>> pq, pqRemove;

    while(Q--)
    {
        cin >> u;
        if (u == 1)
        {
            cin >> v;
            pq.push(v);
        }
        else if (u == 2)
        {
            cin >> v;
            pqRemove.push(v);
        }
        else if (u == 3)
        {
            while(!pqRemove.empty() && pq.top() == pqRemove.top())
            {
                pq.pop();
                pqRemove.pop();
            }
            cout << pq.top() << endl;
        }
    }

    return 0;
}
