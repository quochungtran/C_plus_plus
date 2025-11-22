/**
 * LeetCode 91. Decode Ways
 * https://leetcode.com/problems/decode-ways/
**/

/**
 * ------------------------------------------------------------
 * Key idea:
 * 
 * **** Use DFS + memo(top-down DP) 
 * to count the number of ways we can decode the string bytaking 1 or 2 characters at a time,
 * as long as they form a vadid number (1-26)
 * Time: O(n), Space: O(n)
 * 
 * Notes:
 * dp[i] means: number of way to decode s[i...n-1]
 * A substring startign with '0' is never valid
 * Make sure to hanlde the end of string base case correctly
 * Memorization avoids expontential recursion
 * Carefully to check the 2-digit validity (10-26)
 * ------------------------------------------------------------
 */

class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+1, -1);
        dp[n] = 1;
        return dfs(0, s, dp);
    }

    int dfs(int i, string s, vector<int>& dp){
        if (dp[i] != -1){
            return dp[i];
        }
        if (s[i] == '0'){
            return 0;
        }

        int res = dfs(i+1, s, dp);
        if (i + 1 <= s.size() - 1){
            if (s[i] == '1' || 
               (s[i] == '2' && (s[i+1] >= '0' && s[i+1] <= '6'))
                ){
                res += dfs(i+2, s, dp);
            }
        }
        dp[i] = res;
        return dp[i];
    }
};

/**
 * ------------------------------------------------------------
 * Key idea:
 * **** Use Bottom-up (DP)
 * dp[i] represents the number of ways to decode the substring
 * starting at index i (s[i...n-1])
 * The logic is equivalent to DFS + memo version but filled backwards
 * Complexity Time : O(N), Space: O(N) 
 * 
 * Notes: Always to check '0' first - it cannot start a valid code
 * dp[i] depends on dp[i+1] and dp[i+2] based the codition for validaty of two-digit decoding
 * ------------------------------------------------------------
 */


class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+1, -1);
        dp[n] = 1;

        for (int i = n-1; i >= 0; i--){
            if (s[i] == '0'){
                dp[i] = 0;
            } else {
                dp[i] = dp[i+1];
                if (i+1 <= n-1 &&
                (s[i] == '1' || (s[i]=='2' && s[i+1] < '7'))){
                    dp[i] += dp[i+2];
                }
            }
        }
        return dp[0];
    }
};