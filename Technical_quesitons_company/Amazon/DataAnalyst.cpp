#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

int getMinScore(vector<int>& arr, int s1, int s2)
{
    int n = arr.size();
    int res = n;
    int l = 0;
    unordered_map<int, int> count;
    count[s1] = 0;
    count[s2] = 0;

    for (int r = 0; r < n; r++)
    {
        if (arr[r] == s1)
        {
            count[s1]++;
        }
        if (arr[r] == s2)
        {
            count[s2]++;
        }

        while(count[s1] > 0 && count[s2] > 0)
        {
            res = min(res, r - l + 1);
            if (arr[l] == s1 || arr[l] == s2)
            {
                count[arr[l]]--;
            }
            l++;
        }
    }
    return res;
}

int main()
{  
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int e;
        cin >> e;
        arr.push_back(e);
    } 

    cout << "Min score: " << getMinScore(arr, s1, s2);
    return 0;
}