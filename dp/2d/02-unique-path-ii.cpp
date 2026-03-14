//? https://leetcode.com/problems/unique-paths-ii/description/
/*
You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
    if(i < 0 || j < 0 || grid[i][j])
        return 0;

    if(i == 0 && j == 0) {
        return 1;
    }

    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solveRecursively(grid, i-1, j, dp) + solveRecursively(grid, i, j-1, dp); 
}

int solve(vector<vector<int>>& grid, int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveRecursively(grid, n-1, m-1, dp);
}

int main() {
    int n, m;
    cin>>n>>m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for(int i =0 ;i<n; i++) {
        for(int j =0 ; j<m;j++) 
            cin>>grid[i][j];
    }

    cout<<solve(grid, n, m);
}