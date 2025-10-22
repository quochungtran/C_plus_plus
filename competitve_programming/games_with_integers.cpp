#include "template.hpp"

void solve() {
    ll n;
    in(n);
    
    if (n%3 == 0)
        _print("Second");
    else
        _print("First");
}

int main() {
    FAST_IO
    int t;
    in(t);
    while(t--){
        solve();
    }
}