//* https://leetcode.com/problems/unique-paths/
/*
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(int i, int j, vector<vector<int>>& dp) {
    if(i == 0 && j == 0)
        return 1;
    
    if(i < 0 || j < 0)
        return 0;
    
    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solveRecursively(i-1, j, dp) + solveRecursively(i, j-1, dp);

}

int solveTabulation(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, 0));

    dp[0][0] = 1;

    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            if(i-1 >= 0)
                dp[i][j] += dp[i-1][j];
            if(j-1 >= 0)
                dp[i][j] += dp[i][j-1];
        }
    }
    return dp[n-1][m-1];
}

int solveSpaceOptimized(int n, int m) {
    vector<int> prev(m, 1);

    for(int i = 1; i<n; i++) {
        vector<int> cur(m, 0);
        for(int j = 0; j<m; j++) {
            if(i-1 >= 0)
                cur[j] += prev[j];
            if(j-1 >= 0)
                cur[j] += cur[j-1];
        }
        prev = cur;
    }

    return prev[m-1];
}

int uniquePath(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solveSpaceOptimized(n, m);
}

int main() {
    int n, m;
    cin>>n>>m;
    cout<<uniquePath(n, m);
}
