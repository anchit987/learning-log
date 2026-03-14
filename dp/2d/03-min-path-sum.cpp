//? https://leetcode.com/problems/minimum-path-sum/description/
/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

#include <bits/stdc++.h>
using namespace std;

int findMinPathRecursively(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
    if(i < 0 || j < 0)
        return INT_MAX;
    if(i == 0 && j == 0)
        return grid[i][j];
    
    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = grid[i][j] + min(findMinPathRecursively(grid, i-1, j, dp), findMinPathRecursively(grid, i, j-1, dp));
}

int findMinPathTabulation(vector<vector<int>>& grid, int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            if(i == 0 && j == 0){
                dp[i][j] = grid[i][j];
            } else {
                int up = INT_MAX, left = INT_MAX;

                if(i-1>=0) {
                    up = dp[i-1][j];
                }
                if(j-1>=0) {
                    left = dp[i][j-1];
                }
                
                dp[i][j] = grid[i][j] + min(up, left);
            }
        }
    }
    return dp[n-1][m-1];
}

int findMinPathWithSpaceOptimzation(vector<vector<int>>& grid, int n, int m) {
    vector<int> prev(m, 0);
    
    for(int i = 0; i<n; i++) {
        vector<int> cur(m, 0);
        for(int j = 0; j<m; j++) {
            if(i == 0 && j == 0){
                cur[j] = grid[i][j];
            } else {
                int up = INT_MAX, left = INT_MAX;

                if(i-1>=0) {
                    up = prev[j];
                }
                if(j-1>=0) {
                    left = cur[j-1];
                }
                
                cur[j] = grid[i][j] + min(up, left);
            }
        }
        prev = cur;
    }
    return prev[m-1];
}



int getMinPath(vector<vector<int>>& grid, int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return findMinPathWithSpaceOptimzation(grid, n, m);
}

int main() {
    int n, m;
    cin>>n>>m;

    vector<vector<int>> grid(n, vector<int>(m, 0));
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) 
            cin>>grid[i][j];
    }

    cout<<getMinPath(grid, n, m);
}
