//? https://leetcode.com/problems/target-sum/
/*
    You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

Example 1:

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

*/

#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<int> &nums, int idx, int curSum, int &totalSum, int &target, vector<vector<int>> &dp)
{
    if (idx == -1 && curSum == target)
        return 1;

    if (idx == -1)
        return 0;

    if (dp[idx][curSum + totalSum] != -1)
        return dp[idx][curSum + totalSum];

    // ADD
    int add = solveRecursively(nums, idx - 1, curSum + nums[idx], totalSum, target, dp);
    // SUBS
    int sub = solveRecursively(nums, idx - 1, curSum - nums[idx], totalSum, target, dp);

    return dp[idx][curSum + totalSum] = add + sub;
}

int findTargetSumWays(vector<int> &nums, int target)
{
    int n = nums.size();
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += nums[i];

    vector<vector<int>> dp(n, vector<int>(2 * sum + 1, -1));

    return solveRecursively(nums, n - 1, 0, sum, target, dp);
}

int main()
{
}