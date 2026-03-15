/*
Problem Statement: A thief wants to rob a store. He is carrying a bag of capacity W. The store has ‘n’ items of infinite supply. Its weight is given by the ‘wt’ array and its value by the ‘val’ array. He can either include an item in its knapsack or exclude it but can’t partially have it as a fraction. We need to find the maximum value of items that the thief can steal. He can take a single item any number of times he wants and put it in his knapsack .
Input: n = 3, W = 8, wt = [2, 4, 6], val = [5, 11, 13]
Output: 22
Explanation:We can take item with weight 2 (value 5) four times to fill capacity 8,total value = 5 × 4 = 20.
But a better choice: take item with weight 2 (value 5) twice and item with weight 4 (value 11) once → total weight = 2 + 2 + 4 = 8, total value = 5 + 5 + 11 = 21.
Even better: take two items with weight 4 (value 11 each), total value = 22, which is maximum.

Input: n = 2, W = 3, wt = [2, 1], val = [4, 2]
Output: 6
Explanation:We can take item with weight 1 (value 2) three times , total value = 6.
Taking weight 2 (value 4) plus weight 1 (value 2) also gives 6. No combination yields more than 6.
*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<int>& wt, vector<int>& val, int idx, int curWt, vector<vector<int>>& dp) {
    if(idx < 0 || curWt <= 0)
        return 0;


    if(dp[idx][curWt] != -1)
        return dp[idx][curWt];

    //PICK
    int pick = 0, skip = 0;
    if(wt[idx] <= curWt)
        pick = solveRecursively(wt, val, idx, curWt-wt[idx], dp) + val[idx];
    
    skip = solveRecursively(wt, val, idx-1, curWt, dp);

    return dp[idx][curWt] = max(pick, skip);
}

int unboundKnapsack(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    
    int maxValue = solveRecursively(wt, val, n-1, W, dp);
    return maxValue;
}

int main() {
    int n, W;
    cin>>n>>W;
    vector<int> wt(n), val(n);
    for(int i = 0; i<n; i++) 
        cin>>wt[i];
    
    for(int i = 0; i<n; i++){
        cin>>val[i];
    }
    
    cout<<unboundKnapsack(wt, val, n, W)<<endl;
}