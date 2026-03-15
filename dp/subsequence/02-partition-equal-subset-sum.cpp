//* https://leetcode.com/problems/partition-equal-subset-sum/description/

/*
Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
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

bool isSubsetSumEqualTargetSum(vector<int>& arr, int n, int target) {
    // i -> pick the ith element -> solve(arr, i-1, target-arr[i])
    //  i -> skip -> solve(arr, i-1, target)
    vector<vector<int>> dp(n, vector<int>(target+1, -1));

    return solveRecursively(arr, n-1, target, dp);
}

int main() {
        int n;
        cin>>n;
        vector<int> arr(n);

        int sum = 0;

        for(int i = 0; i<n; i++) {
            cin>>arr[i];
            sum+=arr[i];
        }

    if(sum%2 == 1) {
        cout<<"0";
    } else {
        cout<<isSubsetSumEqualTargetSum(arr, n, sum/2);
    } 

}