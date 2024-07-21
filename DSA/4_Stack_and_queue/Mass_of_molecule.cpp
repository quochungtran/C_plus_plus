#include <iostream>
#include <stack>
#include <string>
using namespace std;

int mass(char c){
    return c == 'H' ? 1 : (c == 'C' : 12 ? 16);
}

int main()
{
    string s;
    cin >> s;

    int queue<int> q;
    int 

    for (auto c : s)
    {
        if (isalpha(c))
        {
            st.push(mass(c));
        }
        if (isdigit(c))
        {
            mass += (c - '0') * st.top();
            st.pop();
        }
        else if (c == '(')
        {
            st.push(-1);
        }
        else if (c == ')')
        {
            w = 0;
            while(st.top() == -1)
            {
                auto val = st.top();
                w += val;
                st.pop();
            }

            weight += w;
            st.pop();
        }
    }

    cout << weight << endl;
}