/**
 * codeforce: Transform the Expression
 * 
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

void transform(string expression){
    stack<char> s;

    for (char sympol: expression){
        if (isalpha(sympol))
        {
            cout << sympol;
        }
        else if (sympol == ')')
        {
            cout << s.top();
            s.pop();
        }
        else if (sympol != '(')
        {
            s.push(sympol);
        }
    }

    cout << endl;
}

int main() {

    int t;
    string expression;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        cin >> expression;
        transform(expression);
    }

    return 0;
}