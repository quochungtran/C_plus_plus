#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

// Record the population point according to the Binary Search Tree list
// with location[x] is the sum of population where the distance to 
// the city is equal to x
// Then traversal the list and sum up the population until geting 
// the target 1 000 000 people.


// Complexity : O(NlogN)

int main()
{
    int numLocation, totalPeople, people;
    double x, y;
    cin >> numLocation, >> totalPeople;    
    map<double, int> location;

    // generate the BST list to record the population according to the increasing key
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> people;
        double r = x * x + y * y;

        if (location.find(r) != location.end())
        {
            location[r] += people;
        }      
        else
        {
            location[r] = people;
        }   
    }

    // travesal the list and sum up the pop each point 
    for (auto loc : location)
    {
        totalPeople += loc.second;
        if (totalPeople >= 1000000)
        {
            cout << fixed << setprecision(6) << sqrt(loc.first) << endl;
            return 0;
        }
    }
    cout << "-1" << endl;
    return 0;
}