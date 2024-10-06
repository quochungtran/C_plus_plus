#include <iostream>
#include <vector>

using namespace std;

// rewrite in utilities
void printVector(const vector<int>& v)
{
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

void nCk(int n,
            int k, 
            const vector<int>&  arr, 
            vector<int>& currComb,
            int start)
{
    if (currComb.size() == k)
        printVector(currComb);
    
    for (int i = start; i < n; i++)
    {
        currComb.push_back(arr[i]);
        nCk(n, k, arr, currComb, i+1); // depend on i to iterate the rest of arr after curr index
        currComb.pop_back();
    }
}


int main()
{
    int number_cases;
    int n, k;
    
    cin >> n >> k;
    vector<int> arr(n, 0);
    vector<bool> check(n, false);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> currComb;
    nCk(n, k, arr, currComb, 0);
}