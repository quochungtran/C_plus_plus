/**
 * codeforce: Throwing_cards_away_I
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <queue>
#include<unordered_map>

using namespace std;

void generateQueue(int n, int c, vector<string>& commands, int id)
{
    cout << "Case " << id <<":" << "\n" ;
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        q.push(i+1);
    }

    for (auto c : commands)
    {
        if (c[0] == 'N')
        {
            int val = q.front();
            q.pop();
            q.push(val);
            cout << val << "\n";
        }
        else if (c[0] == 'E')
        {
            int val = stoi(c.substr(1));
       
            vector<int> tmp;
            while(!q.empty())
            {
                if (val == q.front())
                {
                    q.pop();
                    continue;
                }

                tmp.push_back(q.front());
                q.pop();
            }

            //push the prioritized val on top;
            q.push(val);

            // re-assign again
            for (auto e : tmp)
            {
                q.push(e);
            }

        }
    }
}

int main() {
    
    int N=2, C=2;
    int caseNumber = 1;

    int id = 0;
    while(true)
    {
        cin >> N >> C;
        
        if (N == 0 && C == 0)
            break;

        vector<string> commands(C);
        cin.ignore();

        for (int i = 0; i < C; ++i) {
            getline(cin, commands[i]);
        }

        generateQueue(N, C, commands, caseNumber);
        caseNumber++;
    }
    return 0;
}