#include <iostream>
#include <set>

using namespace std;

int main()
{
    int n;
    set<long long> prices;
    set<long long>::iterator best_buy_idx;
    long long sell_price, minimum_loss = 1e9;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> sell_price;

        // the smaller number which is greater than sell_price
        best_buy_idx = prices.upper_bound(sell_price);
        if (best_buy_idx != prices.end())
        {
            long long loss =  *best_buy_idx - sell_price;
            minimum_loss = min(loss, minimum_loss);
        }

        prices.insert(sell_price);
    }

    cout << minimum_loss;
    return 0;
}