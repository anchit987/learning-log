//? We are given an array ‘ARR’ with N positive integers. We need to find if there is a subset in “ARR” with a sum equal to K. If there is, return true else return false.
/*
A subset/subsequence is a contiguous or non-contiguous part of an array, where elements appear in the same order as the original array.
For example, for the array: [2,3,1] , the subsequences will be [{2},{3},{1},{2,3},{2,1},{3,1},{2,3,1}} but {3,2} is not a subsequence because its elements are not in the same order as the original array.
*/

#include <bits/stdc++.h>
using namespace std;

bool solveRecursively(vector<int>& arr, int i, int target, vector<vector<int>>& dp) {
    if(target == 0)
        return true;
    
    if(i < 0)
        return false;

    if(dp[i][target] != -1) return dp[i][target];

    //? PICK IT
    bool pick = false;
    if(target >= arr[i])
        pick = solveRecursively(arr, i-1, target-arr[i], dp);

    //? SKIP
    bool skip = solveRecursively(arr, i-1, target, dp);

    return dp[i][target] = pick || skip;
}

bool solveTabulation(vector<int>& arr, int n, int target) {
    vector<vector<int>> dp(n, vector<int>(target+1, 0));
    for(int i = 0; i<n; i++)
        dp[i][0] = true;
    if(arr[0] <= target)
        dp[0][arr[0]] = true;

    for(int i = 1; i<n; i++) {
        for(int j = 1; j<=target; j++) {
            //? PICK
            bool pick = false;
            if(arr[i] <= j)
                pick = dp[i-1][j-arr[i]];
            bool skip = dp[i-1][j];

            dp[i][j] = pick || skip;
        }
    }
    return dp[n-1][target];
}

bool solveSpaceOptimized(vector<int>& arr, int n, int target) {
    vector<int> prev(target+1, 0);
    prev[0] = true;
    prev[arr[0]] = true;

    for(int i = 1; i<n; i++) {
        vector<int> cur(target+1, 0);
        cur[0] = 1;

        for(int j = 1; j<=target; j++) {
            //? PICK
            bool pick = false;
            if(arr[i] <= j)
                pick = prev[j-arr[i]];
            bool skip = prev[j];

            cur[j] = pick || skip;
        }
        prev = cur;
    }
    return prev[target];
}

bool isSubsetSumEqualTargetSum(vector<int>& arr, int n, int target) {
    // i -> pick the ith element -> solve(arr, i-1, target-arr[i])
    //  i -> skip -> solve(arr, i-1, target)
    vector<vector<int>> dp(n, vector<int>(target+1, -1));

    return solveSpaceOptimized(arr, n, target);
}

int main() {
    int n, target;
    cin>>n>>target;
    vector<int> arr(n);
    for(int i = 0; i<n; i++) {
        cin>>arr[i];
    }

    cout<<isSubsetSumEqualTargetSum(arr, n, target);
}