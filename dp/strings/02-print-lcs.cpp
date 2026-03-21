#include <bits/stdc++.h>
using namespace std;

int findLCSRecursively(string& str1, string& str2, int i, int j, vector<vector<int>>& dp) {
    // Base Condition
    if(i == 0 || j == 0)
        return 0;

    if(dp[i][j] != -1) 
        return dp[i][j];

    if(str1[i-1] == str2[j-1]) {
        return dp[i][j] = 1 + findLCSRecursively(str1, str2, i-1, j-1, dp);
    } 
    return dp[i][j] = max(findLCSRecursively(str1, str2, i-1, j, dp), findLCSRecursively(str1, str2, i, j-1, dp));
}

int findLCSTabulation(string str1, string str2, int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = 1; i<=n; i++) {
        for(int j = 1; j<=m; j++) {
            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[n][m];
}

int findLCSSpaceOptimized(string str1, string str2, int n, int m) {
    vector<int> prev(m+1, 0), cur(m+1, 0);
    string ans = "";

    for(int i = 1; i<=n; i++) {
        for(int j = 1; j<=m; j++) {
            if(str1[i-1] == str2[j-1]) {
                cur[j] = 1 + prev[j-1];
                ans += str1[i-1];
            } else {
                cur[j] = max(prev[j], cur[j-1]);
            }
        }
        prev = cur;
    }
    cout<<ans<<endl;

    return prev[m];
}

int getLCS(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
    int lcs = findLCSRecursively(str1, str2, n, m, dp);

    int lcsUsingTab = findLCSTabulation(str1, str2, n, m);

    int lcsSpaceOptimzed = findLCSSpaceOptimized(str1, str2, n, m);
    return lcsSpaceOptimzed;
}

int main() {
    string str1, str2;
    cin>>str1>>str2;
    int ans = getLCS(str1, str2);
}