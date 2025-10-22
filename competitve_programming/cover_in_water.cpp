#include "template.hpp"

void solve() {
    ll n;
    std::string s;
    in(n);
    in(s);
    int block_count = 0;
    int count = 0;
    for (auto c : s){
        if (c == '#'){
            block_count = 0;
            continue;
        }
        if (c == '.'){
            count += 1;
            block_count += 1;
        }
        if (block_count == 3){
            _print(2);
            return;
        }
    }        
    _print(count);
}


int main() {
    FAST_IO
    int t;
    in(t);
    while(t--){
        solve();
    }
}