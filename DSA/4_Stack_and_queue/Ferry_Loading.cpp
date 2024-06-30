#include <iostream>
#include <queue>
using namespace std;

int main() {
    int T, ans;
    string s;
    cin >> T;

    for (int i = 0; i < s.length(); i++)
    {
        cin >> s;
        stack<char> expr;
        ans = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '<')
            {
                expr.push(s[i]);
            }
            else if (expr.empty())
            {
                break;
            }
            else
            {
                expr.pop();
                ans = (expr.empty() ? i+1 : ans)
            }
        }
    }
    return 0;
}