#include <bits/stdc++.h>
#include <ranges>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()
#define pb push_pack
#define ppb pop_back
#define mp make_pair


const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const ld EPS = 1e-9;

// ----------------------- input --------------------------
template <class T> 
void in(std::vector<T>& v) {
    for (auto& x : v) std::cin >> x;
}

template <typename... Args>
void in(Args&... args) {
    ((cin >> args), ...);
}

// ----------------------- print --------------------------
template<class T>
void _print(T mess){
    cout << mess;
}

template<class T1, class T2>
auto _print(const pair<T1, T2>& pair){
    cout << "{" << pair.first << ", " << pair.second << "}";
}

// Generic iterable container (vector, set, map, etc.)
// SFINAE ensures this only works if .begin() and .end() exist
template<class Container>
auto _print(const Container& c) -> decltype(c.begin(), c.end(), void()) {
    cout << "[";
    for (auto it = c.begin(); it != c.end(); ++it) {
        _print(*it);
        if (next(it) != c.end()) cout << ", ";
    }
    cout << "]";
}

template<class T>
void print(const T& val) {
    _print(val);
    cout << "\n";
}

// ----------------------- sort --------------------------
template<class T>
void sortArray(vector<T>& a){
    sort(all(a));
}


void solve()
{
    ll n;
    in(n);
    vector<int> a(n);
    in(a);
    string x;
    in(x);
    string s(n, '0');
    vector<int> minLeft(n, 0);
    int minVal = a[0];
    int id = 0;
    for (int i = 1; i < n; i++){
        if (a[i-1] <= minVal){
            minVal = a[i-1];
            id = i-1;
        }
        minLeft[i] = id;
        // cout << minLeft[i] << " ";
    }
    // cout << "\n";

    vector<int> maxRight(n, 0);
    int maxVal = a[n-1];
    id = n-1;
    for (int i = n-2; i >= 0; i--){
        if (a[i+1] >= maxVal){
            maxVal = a[i+1];
            id = i+1;
        }
        maxRight[i] = id;
        // cout << maxRight[i] << " ";

    }
    // cout << "\n";

    vector<pair<int,int>> pairBound;

    for (int i = 1; i < n-1; i++){
        if (a[i] > a[minLeft[i]] && a[i] < a[maxRight[i]]){
            pairBound.push_back({minLeft[i]+1, maxRight[i]+1});
            s[i] = '1';
        }
    }
    // cout << "s " << s << "\n";
    int count  = 0;
    int times = 0;
    vector<int> idx;
    for (int i = 0; i < n; i++)
    {
        if (x[i] == '1'){
            times += 1;
        }
        if (x[i] == '1' && s[i] == '1'){
            idx.push_back(i);
            count += 1;
        }
    }
    if (count < 5 && count >= times){
        print(count);
        for (int i  = 0; i < idx.size(); i++){
            cout << pairBound[i].first + 1 << " " << pairBound[i].second + 1 << "\n";
        }
        return;
    }

    print(-1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    in(t);

    while(t--){
        solve();
    }
}