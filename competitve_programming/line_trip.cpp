#include "template.hpp"

void solve() {
    ll n, x;
    in(n, x);
    vector<ll> a(n);
    in(a);

    ll minimumGas = 0;
    for (int i = 1; i < a.size(); i++){
        minimumGas = max(minimumGas, abs(a[i] - a[i-1]));
    }
    minimumGas = max(minimumGas, abs(a[0]));
    minimumGas = max(minimumGas, 2*abs(x-a[n-1]) );

    _print(minimumGas);
}


int main() {
    FAST_IO
    int t;
    in(t);
    while(t--){
        solve();
    }
}