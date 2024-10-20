#include<bits/stdc++.h>
using namespace std;
 
#define endl  "\n"
#define fastIO {ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
#define MEM(a, b) memset(a, (b), sizeof(a))
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
typedef long long ll;
typedef long long int lli;
 
string s1,s2;
vector<int> missPossition;
 
int calPossition(string &s){
    int ans = 0;
    for(int i = 0 ; i< s.length() ; i++){
        if(s[i] == '+')
            ans++;
        else
            ans--;
    }
    return ans;
}
 
int n,x;
int numOfPermutation;
int numOfCorrect;
 
void Solve(int i){
    if(i == n){
        numOfPermutation++;
        if(calPossition(s2) == x ){
            numOfCorrect++;
        }
    }
    else{
        s2[missPossition[i]] = '+';
        Solve(i+1);
        s2[missPossition[i]] = '-';
        Solve(i+1);
        s2[missPossition[i]] = '?';
    }
}
 
int main(){
	fastIO;
    numOfCorrect = numOfPermutation = 0;
    getline(cin,s1);
    getline(cin,s2);
    x = calPossition(s1);
    for(int i = 0 ; i < s2.length(); i++){
        if(s2[i] == '?')
            missPossition.push_back(i);
    }
    n = missPossition.size();
    if(n == 0){
        if(x == calPossition(s2))
            cout << fixed << setprecision(12) << (double)1;
        else
            cout << fixed << setprecision(12) << (double)0;
        return 0;
    }
    Solve(0);
    cout << fixed << setprecision(12) << numOfCorrect * 1.0 / numOfPermutation;
 
	return 0;
}