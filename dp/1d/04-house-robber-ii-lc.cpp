/*
https://leetcode.com/problems/house-robber-ii/description/

//? "If the houses were in a straight line, standard house robber works fine. But here they're circular — so house[0] and house[n-1] are neighbors. If I blindly apply the same logic, I might rob both of them, which is invalid."

//? "Since house[0] and house[n-1] are neighbors, there are only two possibilities — either I rob house[0] or I rob house[n-1], but never both. So I can fix the circular problem by just guaranteeing that both are never in the same run."


//? "That means I can split this into two completely independent linear problems:

Run 1 — consider houses [0 to n-2]: house[n-1] is excluded, so the circular constraint is gone
Run 2 — consider houses [1 to n-1]: house[0] is excluded, same reason

The answer is just the max of both runs."


INTUITION:
- Houses are in a circle → house[0] and house[n-1] are neighbors
- Split into two linear subproblems:
    Case 1: Rob houses [0 ... n-2]  (exclude last)
    Case 2: Rob houses [1 ... n-1]  (exclude first)
- Answer = max(case1, case2)
*/

#include <bits/stdc++.h>
using namespace std;

// ── APPROACH 1: MEMOIZATION ──────────────────────────────────
// ptr = lower bound of current range (0 or 1)
// Handles negative idx safely: idx < ptr catches idx = -1, -2 too
int solveRecursive(vector<int> &house, int ptr, int idx, vector<int> &dp)
{
    if (idx < ptr)
        return 0;
    if (dp[idx] != -1)
        return dp[idx];

    int pick = house[idx] + solveRecursive(house, ptr, idx - 2, dp);
    int skip = solveRecursive(house, ptr, idx - 1, dp);

    return dp[idx] = max(pick, skip);
}

// ── APPROACH 2: TABULATION ───────────────────────────────────
// BUG FIX: boundary was (i-2 >= 0) → wrong for range [1..n-1]
//          must be (i-2 >= low) to stay within valid range
int solveTabulation(vector<int> &house, int low, int high)
{
    vector<int> dp(high + 1, 0);
    dp[low] = house[low];

    for (int i = low + 1; i <= high; i++)
    {
        int pick = house[i] + (i - 2 >= low ? dp[i - 2] : 0); // FIX: >= low not >= 0
        int skip = dp[i - 1];
        dp[i] = max(pick, skip);
    }

    return dp[high];
}

// ── APPROACH 3: SPACE OPTIMIZED ──────────────────────────────
// dp[i] depends only on dp[i-1] and dp[i-2] → use two variables
// prev2 = 0 naturally handles the (i-2 < low) boundary case
int solveSpaceOptimized(vector<int> &house, int low, int high)
{
    if (low == high)
        return house[low];

    int prev2 = 0;
    int prev1 = house[low];

    for (int i = low + 1; i <= high; i++)
    {
        int pick = house[i] + prev2;
        int skip = prev1;
        int cur = max(pick, skip);
        prev2 = prev1;
        prev1 = cur;
    }

    return prev1;
}

int rob(vector<int> &house)
{
    int n = house.size();

    // Edge cases
    if (n == 1)
        return house[0];
    if (n == 2)
        return max(house[0], house[1]);

    // Approach 1: Memoization
    vector<int> memo(n, -1);
    int memo1 = solveRecursive(house, 0, n - 2, memo);
    memo.assign(n, -1); // reset; note dp[0] unused in 2nd call
    int memo2 = solveRecursive(house, 1, n - 1, memo);

    // Approach 2: Tabulation
    int tab1 = solveTabulation(house, 0, n - 2);
    int tab2 = solveTabulation(house, 1, n - 1);

    // Approach 3: Space Optimized — return this in final interview answer
    int opt1 = solveSpaceOptimized(house, 0, n - 2);
    int opt2 = solveSpaceOptimized(house, 1, n - 1);

    return max(opt1, opt2);
}

int main()
{
    int n;
    cin >> n;
    vector<int> house(n);
    for (int i = 0; i < n; i++)
        cin >> house[i];

    cout << rob(house) << endl;
    return 0;
}

/*
COMPLEXITY:
  Time  → O(n) all approaches
  Space → O(n) memo, O(n) tabulation, O(1) space optimized
*/