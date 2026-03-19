/*
Problem Statement: Given a rod of length N inches and an array price[] where price[i] denotes the value of a piece of rod of length i inches (1-based indexing). Determine the maximum value obtainable by cutting up the rod and selling the pieces. Make any number of cuts, or none at all, and sell the resulting pieces.
Input : price = [1, 6, 8, 9, 10, 19, 7, 20], N = 8
Output :25
Explanation :Cut the rod into lengths of 2 and 6 for a total price of 6 + 19= 25.

Input :price = [1, 5, 8, 9], N = 4
Output :10
Explanation :Cut the rod into lengths of 2 and 2 for a total price of 5 + 5 = 10.
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<int>& arr, int idx, int len, vector<vector<int>>& dp) {
    // BASE Condition
    if(len == 0)
        return 0;

    if(idx < 0 || len < 0)
        return INT_MIN;
    
    if(dp[idx][len] != -1) return dp[idx][len];

    // PICK THE CURRENT ELEMENT
    int pick = 0;
    if((idx+1) <= len) {
        pick = arr[idx] + solveRecursively(arr, idx, len-(idx+1), dp);
    }
    int skip = solveRecursively(arr, idx-1, len, dp);

    return dp[idx][len] = max(pick, skip);
}

int solveTabulation(vector<int>& arr, int n, int len) {
    vector<vector<int>> dp(n, vector<int>(len+1, 0));
    
    for(int i = 1; i<=len; i++) {
        dp[0][i] = arr[0]*i;
    }

    for(int i = 1; i<n; i++) {
        for(int j = 1; j<=len; j++) {
            int pick = 0;
            if(i+1 <= j) {
                pick = arr[i] + dp[i][j-(i+1)];
            }
            int skip = dp[i-1][j];
            dp[i][j] = max(pick, skip);
        }
    }
    return dp[n-1][len];
}

int solveSpaceOptimized(vector<int>& arr, int n, int len) {
    vector<int> prev(len+1, 0);
    for(int i = 1; i<n; i++) {
        prev[i] = i*arr[0];
    }

    for(int i = 1; i<n; i++) {
        vector<int> cur(len+1, 0);
        for(int j = 1; j<=len; j++) {
            int pick = 0;
            if(i+1 <= j) {
                pick = arr[i] + cur[j-(i+1)];
            }
            int skip = prev[j];
            cur[j] = max(pick, skip);
        }
        prev = cur;
    }
    return prev[len];
}

int findMaxValForRodLen(vector<int>& arr, int n, int len) {
    // idx -> Pick it or Skip it -> this will create the recursive tree -> we do find overlapping 
    // subproblem -> we can memoize that 
    vector<vector<int>> dp(n, vector<int>(len+1, -1));
    int maxVal = solveRecursively(arr, n-1, len, dp);
    return solveSpaceOptimized(arr, n, len);
}

int main() {
    int n, len;
    cin>>n>>len;
    vector<int> arr(n);
    for(int i = 0; i<n; i++) {
        cin>>arr[i];
    }

    cout<<findMaxValForRodLen(arr, n, len);
}