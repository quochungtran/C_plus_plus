#include <bits/stdc++.h>

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


void solve();

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    in(t);

    while(t--){
        solve();
    }
}