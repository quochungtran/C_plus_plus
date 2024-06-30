#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

int main() {
    int P, C, x, temp, tc = 1;
    char cmd;
    queue<int> q;

    while (true) {
        cin >> P >> C;
        if (P == 0 && C == 0) {
            break;
        }

        for (int i = 1; i <= min(P, C); i++) {
            q.push(i);
        }

        cout << "Case " << tc++ << ":" << endl;

        for (int i = 0; i < C; i++) {
            cin >> cmd;

            if (cmd == 'N') {
                temp = q.front();
                cout << temp << endl;
                q.pop();
                q.push(temp);
            }
            else {
                cin >> x;
                int n = q.size();
                q.push(x);
                
                for (int j = 0; j < n; j++) {
                    temp = q.front();
                    q.pop();
                    if (temp != x) {
                        q.push(temp);
                    }
                }
            }
        }

        while (!q.empty()) {
            q.pop();
        }
    }
    return 0;
}