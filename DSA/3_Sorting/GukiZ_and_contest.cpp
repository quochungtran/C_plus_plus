/**
 * codeforce: GukiZ and Contest
 * 
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int, vector<int>, greater<int>> construit_map(vector<int>& arr){
    
    map<int, vector<int>, greater<int>> mp;
    for (int i = 0; i < arr.size(); i++)
    {
        mp[arr[i]].push_back(i);
    }

    return mp;
}

vector<int> build_rating(map<int, vector<int>, greater<int>>& mp, vector<int>& arr)
{
    vector<int> res(arr.size()); 
    int pos = 1;

    for (auto [k, v]: mp)
    {
        for (auto id : v)
        {
            res[id] = pos;
        }
        pos += v.size();
    }

    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    auto mp  = construit_map(arr);    
    auto res = build_rating(mp, arr);

    for (auto e : res)
    {
        cout << e << " ";
    }
    return 0;
}