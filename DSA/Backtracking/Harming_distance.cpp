#include <iostream>

using namespace std;

void hamming_distance(int n, int h, string res, int start, int index)
{
    if (index == h)
    {
        return res;
        return;
    }

    for (int i = n-h+1; i >= start; i--)
    {
        res[i] = '1';
        hamming_distance(n, h, res, i+1, index+1);
        res[i] = '0';
    }
}

int main()
{
    int num_datasets;
    cin >> num_datasets;
    
    while(num_datasets--)
    {
        int n, h;
        cin >> n >> h;

        string res(n, '0');
        hamming_distance(n, h, res, 0, 0);
    }

    return 0;
}