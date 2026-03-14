#include <bits/stdc++.h>
using namespace std;

// PROBLEM STATEMENT:
// A frog wants to climb a staircase with n steps. Given an integer array heights, where heights[i] contains the height of the ith step, and an integer k. To jump from the ith step to the jth step, the frog requires abs(heights[i] - heights[j]) energy, where abs() denotes the absolute difference. The frog can jump from the ith step to any step in the range [i + 1, i + k], provided it exists. Return the minimum amount of energy required by the frog to go from the 0th step to the (n-1)th step.
/*
Example 1:
Input: heights = [10, 5, 20, 0, 15], k = 2
Output: 15
Explanation:
0th step -> 2nd step, cost = abs(10 - 20) = 10
2nd step -> 4th step, cost = abs(20 - 15) = 5
Total cost = 10 + 5 = 15.

Example 2:
Input: heights = [15, 4, 1, 14, 15], k = 3
Output: 2
Explanation:
0th step -> 3rd step, cost = abs(15 - 14) = 1
3rd step -> 4th step, cost = abs(14 - 15) = 1
Total cost = 1 + 1 = 2.
*/

int calMinEnergyRecursively(vector<int> &h, int idx, int k, vector<int> &dp)
{
    if (idx == 0)
        return 0;

    if (dp[idx] != -1)
        return dp[idx];

    int minEnergy = INT_MAX;

    //! Explain
    //? "Instead of thinking forward — 'where can I go from here?' — I flip it and think backward:
    //? 'To reach step idx, which step could I have come from?'
    //?If I'm at step idx, the frog must have jumped from somewhere in the range [idx-k, idx-1].
    //? So I try all possible previous steps, compute the cost for each, and take the minimum."

    for (int i = idx - 1; i >= idx - k && i >= 0; i--)
    {
        //? For each candidate step i, I ask - what's the minimum energy to reach step i? Then I add the cost of jumping from i to idx, which is abs(h[i] - h[idx]). I track the minimum across all candidates.

        int jump = calMinEnergyRecursively(h, i, k, dp) + abs(h[i] - h[idx]);
        minEnergy = min(minEnergy, jump);
    }
    return dp[idx] = minEnergy;
}

int calMinEnergy(int n, int k, vector<int> &h)
{
    // Memoization
    vector<int> dp(n, -1);
    int memoAns = calMinEnergyRecursively(h, n - 1, k, dp);
    return memoAns;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (int i = 0; i < n; i++)
        cin >> h[i];

    int ans = calMinEnergy(n, k, h);
    cout << ans << endl;
}