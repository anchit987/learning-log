/*
Problem Statement: Given an array of N positive integers, we need to return the maximum sum of the subsequence such that no two elements of the subsequence are adjacent elements in the array.

Input: nums = [1, 2, 4]
Output: 5
Explanation:
Subsequence {1,4} gives maximum sum.

Input:  [2, 1, 4, 9]
Output: 11
Explanation:
Subsequence {2,9} gives maximum sum
*/

#include <bits/stdc++.h>
using namespace std;

int calcMaxSumRecursively(vector<int> &arr, int idx, vector<int> &dp)
{
    if (idx < 0)
        return 0;
    if (dp[idx] != -1)
        return dp[idx];

    //* PICK IT
    int pick = arr[idx] + calcMaxSumRecursively(arr, idx - 2, dp);

    //* SKIP
    int skip = calcMaxSumRecursively(arr, idx - 1, dp);

    return dp[idx] = max(pick, skip);
}

int calMaxSum(vector<int> arr, int n)
{
    vector<int> memo(n, -1);
    int maxSum = calcMaxSumRecursively(arr, n - 1, memo);

    vector<int> dp(n, 0);
    dp[0] = arr[0];

    for (int i = 1; i < n; i++)
    {
        int prev = i - 2 >= 0 ? dp[i - 2] : 0;

        int pick = arr[i] + prev;
        int skip = dp[i - 1];
        dp[i] = max(pick, skip);
    }

    //? Instead of storing all N values, I only keep two variables: prev1 and prev2 and slide them forward each iteration. Same logic as space optimizing Fibonacci. This brings space from O(N) to O(1).

    int prev1 = arr[0];
    int prev2 = 0;

    for (int i = 1; i < n; i++)
    {
        int pick = arr[i] + prev2;
        int skip = prev1;
        int cur = max(pick, skip);

        prev2 = prev1;
        prev1 = cur;
    }

    return prev1;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << calMaxSum(arr, n) << endl;

    return 0;
}