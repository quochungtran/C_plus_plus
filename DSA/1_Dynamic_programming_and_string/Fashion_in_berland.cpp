#include <iostream>  
#include <vector>

using namespace std;

bool checkJacket(vector<int>& v, int n)
{
    if (n==1){
        if (v[0] == 1)
            return true
        else
            return false;
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == 0)
        {
            count++;
        }
    }

    if (count == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main() {
    int n, value;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        v.push_back(value);
    }

    bool result = checkJacket(v, n);
    if (result == true)
    {
        cout << "YES";
    }
    else
        cout << "NON";
    
    return 0;
}