/**
 * LeetCode 139. Word Break
 * https://leetcode.com/problems/word-break/
**/


/*
 * (Bottom-up approach)
 */

class Solution {

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto n = s.size();
        vector<bool> dp(n+1, false);
        dp[n] = true;
        for (int i = n-1; i >= 0; i--){
            for (auto word: wordDict){
                int lenWord = word.size();
                if (i + lenWord <= n && 
                    (s.substr(i, lenWord) == word && dp[i+lenWord]) ){
                    dp[i] = true;
                }
            }
        }

        return dp[0];
    }
};