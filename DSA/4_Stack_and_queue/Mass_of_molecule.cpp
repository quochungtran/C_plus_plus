/**
 * codeforce: Throwing_cards_away_I
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <queue>
#include<unordered_map>
#include<cctype>

using namespace std;

bool isUpperCaseAlphabet(char c) {
    return c >= 'A' && c <= 'Z';
}

int main() {
    
    string s;
    getline(cin, s);

    int i = 0;
    int n  = s.size() ;
    stack<char> st;

    unordered_map<char, int> mass{{'C', 12}, {'H', 1}, {'O', 16}};

    int res = 0;

    while(i <= n-1)
    {
        if (s[i] != ')')
        {
            st.push(s[i]);
            cout << st.top() << " ,";
        }
        else //if (s[i] == ')')
        {
            int ele = 0;
            while(!st.empty() && st.top() != '(')
            {
                if (isUpperCaseAlphabet(s[i]))
                {
                    ele += mass[st.top()];
                    st.pop();
                }

                // if (isalpha(s[i]))
                // {
                //     int factor = st.top() - '0';
                //     st.pop();
                //     ele += st.top() * factor;
                // }

            }
            st.pop();

            if (i+1 <= n-1 && isalpha(s[i+1]))
            {
                ele = ele * s[i+1];
                i++;
            }
        }
        i++;
    }

    cout << res;

    return 0;
}