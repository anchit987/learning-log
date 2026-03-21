#include <bits/stdc++.h>
using namespace std;

int findLCS(string a, string b, int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = 1; i<=n; i++) {
        for(int j = 1; j<=m; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[n][m];
}

int getLPS(string a) {
    int n = a.size();
    string b = a;
    int m = n;
    reverse(b.begin(), b.end());
    
    return findLCS(a, b, n, m);
}

int main() {
    string str;
    cin>>str;

    cout<<getLPS(str);

    //! Minimum insertions to make string palindrome 
    //? string.size() - getLPS(str);
}