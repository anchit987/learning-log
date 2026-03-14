//? https://leetcode.com/problems/triangle/description/
/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

 

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
Example 2:

Input: triangle = [[-10]]
Output: -10
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<vector<int>>& triangle, int i, int j, int n, vector<vector<int>>& dp) {
    if(i == n-1)
        return triangle[i][j];
    
    if(dp[i][j] != -1) return dp[i][j];

    int down = solveRecursively(triangle, i+1, j, n, dp);
    int diag = solveRecursively(triangle, i+1, j+1, n, dp);

    return dp[i][j] = triangle[i][j] + min(down, diag);
}

int solveTabulation(vector<vector<int>>& triangle, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][0] = triangle[0][0];

    for(int i = 1; i<n; i++) {
        for(int j = 0; j<=i; j++) {

            int up = INT_MAX;
            if(j < i)
                up = dp[i-1][j];
            int diag = INT_MAX;
            if(j > 0)
                diag = dp[i-1][j-1];
            dp[i][j] = triangle[i][j] + min(up, diag);
        }
    }
    int minSum = INT_MAX;
    for(int i = 0; i<n; i++)
        minSum = min(minSum, dp[n-1][i]);
    return minSum;
}

int solveSpaceOptimized(vector<vector<int>>& triangle, int n) {
    vector<int> prev(n, 0);
    prev[0] = triangle[0][0];

    for(int i = 1; i<n; i++) {
        vector<int> cur(n, 0);
        for(int j = 0; j<=i; j++) {
            int up = INT_MAX;
            if(j < i)
                up = prev[j];
            int diag = INT_MAX;
            if(j > 0)
                diag = prev[j-1];
            cur[j] = triangle[i][j] + min(up, diag);
        }
        prev = cur;
    }
    int minSum = INT_MAX;
    for(int i = 0; i<n; i++)
        minSum = min(minSum,prev[i]);
    return minSum;
}

int findMinPath(vector<vector<int>>& triangle, int n) {
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solveSpaceOptimized(triangle, n);
}

int main() {
    int n;
    cin>>n;

    vector<vector<int>> triangle(n, vector<int>(n, 0));

    for(int i = 0; i<n; i++) {
        for(int j = 0; j<=i; j++) 
            cin>>triangle[i][j];
    }

    cout<<findMinPath(triangle, n);
}