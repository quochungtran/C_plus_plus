/**
 * 322. Coin Change
 * https://leetcode.com/problems/decode-ways/
**/

/* DP Top-down 
 * 
**/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, -1);
        auto res = dfs(amount, coins, dp);
        if (res == 1e9){
            return -1;
        }
        return res;
    }

    int dfs(int amount, vector<int>& coins, vector<int>& dp){
        if (amount == 0){
            return 0;
        }

        if (dp[amount] != -1){
            return dp[amount];
        }

        int result = 1e9;
        int n = coins.size();
        for (int i = 0; i < n; i++){
            if (amount - coins[i] >= 0){
                result = min(result, 1 + dfs(amount - coins[i], coins, dp));
            }
        }
        dp[amount] = result;
        return dp[amount];
    }
};

/* Bottom up 
 * dp[i] (dp[0...amount]) -> indicate the fewest number of coins that need to make up amount i
 * Complexity Time: O(n*t), Space: O(t) ; n is the number of coins, t is given amount
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, 1e9);
        dp[0] = 0;
        int n = coins.size();
        for (int i = 0 ; i < n; i++){
            for (int amt = 0; amt <= amount; amt++){
                if (amt - coins[i] >= 0){
                    dp[amt] = min(dp[amt], 1 + dp[amt - coins[i]]); 
                }
            }
        }
        if (dp[amount] == 1e9)
            return -1;
        return dp[amount];

    }
};