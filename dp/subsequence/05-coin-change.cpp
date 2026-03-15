//? https://leetcode.com/problems/coin-change/description/
/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<int>& arr, int idx, int amt, vector<vector<int>>& dp) {
    if(amt == 0) {
        return 0;
    }
    if(idx < 0)
        return INT_MAX;

    if(dp[idx][amt] != -1)
        return dp[idx][amt];

    //? PICK
    int pick = INT_MAX, skip = INT_MAX;
    if(arr[idx] <= amt) {
        int temp = solveRecursively(arr, idx, amt-arr[idx], dp);
        if(temp != INT_MAX)
            pick = 1 + temp;

    }
    skip = solveRecursively(arr, idx-1, amt, dp);

    return dp[idx][amt] = min(pick, skip);
}

int solveTabulation(vector<int>& arr, int n, int amount) {

    int INF = INT_MAX/2;
    vector<vector<int>> dp(n, vector<int>(amount+1, INF));
    
    for(int i = 0; i<n ;i++)
        dp[i][0] = 0;

    for(int i = 0; i<n; i++) {
        for(int j = 1; j<=amount; j++) {
            //? PICK
            int pick = INF, skip = INF;
            if(arr[i]<=j && dp[i][j-arr[i]] != INF) {
                pick = 1 + dp[i][j-arr[i]];
            }
            skip = (i > 0) ? dp[i-1][j] : INF;

            dp[i][j] = min(pick, skip);
        }
    }
    
    return dp[n-1][amount];
}

int solveSpaceOptimized(vector<int>& arr, int n, int amount) {

    int INF = INT_MAX/2;
    vector<int> prev(amount+1, INF);
    
    prev[0] = 0;

    for(int i = 0; i<n; i++) {
        vector<int> cur(amount+1, INF);
        cur[0] = 0;
        for(int j = 1; j<=amount; j++) {
            //? PICK
            int pick = INF, skip = INF;
            if(arr[i]<=j && cur[j-arr[i]] != INF) {
                pick = 1 + cur[j-arr[i]];
            }
            skip = (i > 0) ? prev[j] : INF;

            cur[j] = min(pick, skip);
        }
        prev = cur;
    }
    
    return prev[amount];
}

int minCoinRequired(vector<int>& arr, int n, int amount) {
    sort(arr.begin(), arr.end());
    vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    int minCoin = solveSpaceOptimized(arr, n, amount);


    return (minCoin == INT_MAX/2 ? -1 : minCoin);

}

int main() {
    int n, amount;
    cin>>n>>amount;
    
    vector<int> arr(n);
    for(int i = 0; i<n; i++)
        cin>>arr[i];

    cout<<minCoinRequired(arr, n, amount);
}