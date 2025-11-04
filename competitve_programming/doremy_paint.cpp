#include "template.hpp"

/**
 * Note rbegin() used here to indicate the last element of the map 
 * meanwhile begin() point to the first element
 */

void solve() {
    int n;
    in(n);
    vector<int> a(n);
    in(a);
    map<int, int> mp;

    for (int i = 0; i < n; i++){
        mp[a[i]] += 1;
    }

    if (mp.size() == 1){
        print("YES");
    }
    else if (mp.size() == 2){
        auto firstCount  = mp.begin()->second;
        auto secondCount = mp.rbegin()->second;
        if (firstCount == secondCount){
            print("YES");
        } 
        else if (n%2 == 1 && abs(firstCount - secondCount) == 1){
            print("YES");
        }
        else{
            print("NO");
        }
    }
    else{
        print("NO");
    }
    return;
}
