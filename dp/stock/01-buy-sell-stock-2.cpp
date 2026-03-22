#include <bits/stdc++.h>
using namespace std;

int solveRecursively(vector<int>& values, int idx, int flag) {
    if(idx == values.size())
        return 0;
    
    int profit = 0;
    if(flag == 1) {
        //* BUY IT
        profit = -values[idx] + solveRecursively(values, idx+1, 0);
        //* SKIP IT
        profit = max(profit, solveRecursively(values, idx+1, 1));
    } else {
        //* SELL IT
        profit = values[idx] + solveRecursively(values, idx+1, 1);
        //* SKIP IT
        profit = max(profit, solveRecursively(values, idx+1, 0));
    }
    
    return profit;
}

int solveTabulation(vector<int>& values, int n) {
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][1] = -values[0];
    dp[0][0] = 0;

    for(int i = 1; i<n; i++) {
        for(int j = 0; j<2; j++) {
            int profit = 0;
            if(j == 1) {
                //* BUY
                //* If I'm buying it, then in the previous idx
                profit = -values[i] + dp[i-1][0];
                //* I can skip the buying
                profit = max(profit, dp[i-1][1]);
            } else {
                //* SELL
                //* I can sell it
                profit = values[i] + dp[i-1][1];
                //* Skip sell
                profit = max(profit, dp[i-1][0]);
            }
            dp[i][j] = profit;
        }
    }
    return max(dp[n-1][0], dp[n-1][1]);
}

int solveTabulation2(vector<int>& values, int n) {
    vector<vector<int>> dp(n+1, vector<int>(2, 0));

    for(int i = n-1; i>=0; i--) {
        for(int flag = 0; flag < 2; flag++) {
            int profit = 0;
            if(flag == 1) {
                profit = max(
                    -values[i] + dp[i+1][0], //* BUYING
                    dp[i+1][1] //* SKIP
                );
            } else {
                profit = max(
                    values[i] + dp[i+1][1], //* SELLING
                    dp[i+1][0] //* SKIP
                );
            }
            dp[i][flag] = profit;
        }
    }
    return dp[0][1];
}



int getMaxProfit(vector<int>& values, int n) {
    // 4 7 3 9 8 10
    
    return solveTabulation2(values, n);
}

int main() {
    int n;
    cin>>n;
    vector<int> values(n);
    for(int i = 0; i<n ; i++) {
        cin>>values[i];
    }
    cout<<solveTabulation2(values, n);
}