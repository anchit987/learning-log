#include <bits/stdc++.h>
using namespace std;

/*
 * NOTE FOR FUTURE: Longest Common Substring (Contiguous) - Avoid Recursive Approach
 *
 * Do NOT attempt a top-down recursive + memoization solution for this problem in interviews.
 * The core issue is that the "current streak" (cnt) is part of the state, meaning the dp
 * table would need to be 3D: dp[i][j][cnt] — awkward, hard to reason about under pressure,
 * and easy to get wrong. The classic mistake is passing cnt as a parameter but only using
 * a 2D dp table, which causes incorrect cache hits when two calls share the same (i, j) but
 * have different streak lengths. Bottom-up is the right instinct here from the start.
 *
 * The key insight that makes bottom-up clean: redefine dp[i][j] as the length of the longest
 * common substring ENDING at str1[i-1] and str2[j-1]. With this framing, the recurrence is
 * just two lines — extend the streak by 1 if characters match (dp[i][j] = dp[i-1][j-1] + 1),
 * or reset to 0 if they don't. You track a global max separately. No recursion, no stack
 * overhead, no tricky state management. This is also what distinguishes substring from
 * subsequence — in subsequence (LCS), a mismatch takes max(dp[i-1][j], dp[i][j-1]); in
 * substring, a mismatch resets to 0 because the contiguous streak is broken.
 *
 * Rule of thumb: whenever "current streak" or "current count" is part of your recursive
 * state, it's a strong signal to go bottom-up immediately. The "ending at (i, j)" 
 * reframing almost always absorbs that extra dimension cleanly.
 */

int findLCSubstringRecursively(string& str1, string& str2, int i, int j, int cnt) {
    if(i == 0 || j == 0) 
        return cnt;

    if(str1[i-1] == str2[j-1])
        return findLCSubstringRecursively(str1, str2, i-1, j-1, cnt+1);
    
    return max(findLCSubstringRecursively(str1, str2, i-1, j, 0), findLCSubstringRecursively(str1, str2, i, j-1, 0));
}

// ! Since dp[i][j] = length of common substring ENDING at str1[i-1], the substring's
// ! start is always (endIdx - maxLen) in 0-based. So just track where maxLen last
// ! updated (endIdx = i), and substr() does the rest - no dp backtracking needed.
int findLCSTab(string& str1, string& str2, int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    int maxLen = 0;
    int endIdx = 0;

    for(int i = 1; i<=n; i++) {
        for(int j = 1; j<=m; j++) {
            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                if(maxLen < dp[i][j]) {
                    maxLen = dp[i][j];
                    endIdx = i;
                }

            } else {
                dp[i][j] = 0;
            }
        }
    }
    // ! substring ends at endIdx-1 (0-based) with length maxLen
    cout<<str1.substr(endIdx - maxLen, maxLen)<<endl;

    return maxLen;
}

int findLCSTabOptimized(string& str1, string& str2, int n, int m) {
    vector<int> prev(m+1, 0), cur(m+1,  0);
    int maxLen = 0;
    for(int i = 1; i<=n; i++) {
        for(int j = 1; j<=m; j++) {
            if(str1[i-1] == str2[j-1]) {
                cur[j] = 1 + prev[j-1];
                maxLen = max(maxLen, cur[j]);
            } else {
                cur[j] = 0;
            }
        }
        prev = cur;
    }

    return maxLen;
}


int getLCSubstring(string str1, string str2) {
    int n = str1.size(), m = str2.size();
    int lcs = findLCSubstringRecursively(str1, str2, n, m, 0);

    int lcsTab = findLCSTab(str1, str2, n, m);
    
    return findLCSTabOptimized(str1, str2, n, m);
}

int main() {
    string str1, str2;
    cin>>str1>>str2;

    cout<<getLCSubstring(str1, str2);
}