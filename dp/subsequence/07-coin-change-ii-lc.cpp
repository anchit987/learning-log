//? https://leetcode.com/problems/coin-change-ii/description/
/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.
Example 1:

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<int>& arr, int idx, int amt, vector<vector<int>>& dp) {
    if(amt == 0)
        return 1;
    
    if(idx < 0 || amt < 0)
        return 0;
    
    if(dp[idx][amt] != -1)
        return dp[idx][amt];

    //? PICK
    int pick = 0, skip = 0;
    if(arr[idx] <= amt) {
        pick = solveRecursively(arr, idx, amt-arr[idx], dp);
    }
    //?SKIP
    skip = solveRecursively(arr, idx-1, amt, dp);

    return dp[idx][amt] = pick+skip;
}

int coinChange(vector<int> arr, int n, int amount) {
    vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    int noOfWays = solveRecursively(arr, n-1, amount, dp);

    return noOfWays;
}

int main() {
    int n, amount;
    cin>>n>>amount;
    vector<int> arr(n);
    for(int i = 0; i<n; i++)
        cin>>arr[i];
    cout<<coinChange(arr, n, amount);
}