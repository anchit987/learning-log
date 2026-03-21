#include <bits/stdc++.h>
using namespace std;

//! https://leetcode.com/problems/edit-distance/

class Solution {
public:
    int findLCS(string a, string b, int n, int m) {
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for(int i = 0; i<=n; i++)
            dp[i][0] = i;
        for(int j = 0; j<=m; j++)
            dp[0][j] = j;

        for(int i = 1; i<=n; i++) {
            for(int j = 1; j<=m; j++) {
                if(a[i-1] == b[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1]));
                }
            }
        }
        
        return dp[n][m];
    }
    int minDistance(string word1, string word2) {
        int lcs = findLCS(word1, word2, word1.size(), word2.size());
        return lcs;
    }
};


int main() {
    
}