#include <bits/stdc++.h>
using namespace std;

//! https://leetcode.com/problems/distinct-subsequences/
//! see leetcode solution

class Solution {
public:
    int lcs(string& s, string& t, int i, int j, vector<vector<int>>& dp) {
        if(j < 0){
            return 1;
        }
        if(i < 0)
            return 0;
        if(dp[i][j] != -1)
            return dp[i][j];

        int pick = 0;
        int skip = 0;
        if(s[i] == t[j])
            pick = lcs(s, t, i-1, j-1, dp);
        
        skip = lcs(s, t, i-1, j, dp);
        return dp[i][j] = pick + skip;
    }

    int lcsTabulation(string& s, string& t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        dp[0][0] = 1;
        for(int i = 0; i<=n; i++) 
            dp[i][0] = 1;

        for(int i = 1; i<=n ;i++) {
            for(int j = 1; j<=m; j++) {
                long long pick = 0, skip = 0;
                if(s[i-1] == t[j-1])
                    pick = dp[i-1][j-1];
                skip = dp[i-1][j];
                dp[i][j] = min(pick + skip, (long long) INT_MAX);
            }
        }
        return dp[n][m];
    }

    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return lcsTabulation(s, t);
    }
};