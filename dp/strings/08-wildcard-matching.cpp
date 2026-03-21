#include <bits/stdc++.h>
using namespace std;

//! https://leetcode.com/problems/wildcard-matching/description/

class Solution {
public:
    bool isAllStar(string& p, int j) {
        while(j >= 0) {
            if(p[j] != '*')
                return false;
            j--;
        }
        return true;
    }
    bool wildMatch(string& s, string& p, int i, int j, vector<vector<int>>& dp) {
        if(i < 0 && j < 0)
            return true;
        if(i < 0) {
            return isAllStar(p, j);
        }
        if(i < 0 || j <0)
            return false;

        if(dp[i][j] != -1)
            return dp[i][j];
        
        bool ans = false;
        if(s[i] == p[j] || p[j] == '?') {
            ans = wildMatch(s, p, i-1, j-1, dp);
        } else if(p[j] == '*') {
            ans = (ans || wildMatch(s, p, i-1, j, dp));
            ans = (ans || wildMatch(s, p, i, j-1, dp));
        } 
        return dp[i][j] = ans;
    }

    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return wildMatch(s, p, n-1, m-1, dp);
    }
};

int main() {
    
}