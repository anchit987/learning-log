//? https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/
/*
You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.

Return the minimum possible absolute difference.

Example 1:
Input: nums = [3,9,7,3]
Output: 2
Explanation: One optimal partition is: [3,9] and [7,3].
The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.

Example 2:
Input: nums = [-36,36]
Output: 72
Explanation: One optimal partition is: [-36] and [36].
The absolute difference between the sums of the arrays is abs((-36) - (36)) = 72.
*/

#include <bits/stdc++.h>
using namespace std;

int minPartitionDiff(vector<int>& arr, int n, int sum) {
    //! LETS TRY SOLVING THIS DIRECTLOY USING TABULATION APPROACH

    vector<vector<bool>> dp(n, vector<bool>(sum+1, false));

    for(int i = 0; i<n; i++)
        dp[i][0] = true;
    
    dp[0][arr[0]] = true;

    for(int i = 1; i<n; i++) {
        for(int j = 1; j<=sum; j++) {
            //? Pick
            bool pick = false;
            if(arr[i]<=j) {
                pick = dp[i-1][j-arr[i]];
            }
            bool skip = dp[i-1][j];
            dp[i][j] = pick || skip;
        }
    }
    int minDiff = INT_MAX;
    for(int i = 0; i<=sum; i++) {
        if(dp[n-1][i]) {
            minDiff = min(minDiff, abs(i-(sum-i)));
        }
    }

    return minDiff;
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

    cout<<minPartitionDiff(arr, n, sum);


}