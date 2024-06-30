/**
 * codeforce: Street Parade
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

void streetParade(vector<int>& arr, vector<string>& outputs)
{
    int n = arr.size();
    stack<int> st;
    vector<int> res;
    int currMin = 1;

    for (int i=0; i < n; i++)
    {
        if (arr[i] > currMin)
        {
            while(!st.empty() && st.top() == currMin)
            {
                res.push_back(st.top());
                st.pop();
                currMin++;
            }

            st.push(arr[i]);
        }
        else if (arr[i] == currMin)
        {
            res.push_back(currMin);
            currMin++;
        }
    }

    while(!st.empty())
    {
        int val = st.top();
        res.push_back(val);
        st.pop();
    }

    for (int i = 0; i < n; i++)
    {
        if (res[i] != i+1)
        {
            outputs.push_back("no");
            return;
        }
    }

    outputs.push_back("yes");
}

int main() {
    
    vector<string> outputs;

    while(true)
    {
        int n;
        cin >> n;
        if (n == 0)
        {
            break;
        }

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        streetParade(arr, outputs);    
    }
    for (auto o: outputs)
    {
        cout << o << "\n";
    }
    return 0;
}