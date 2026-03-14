#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int prev = 1; // n = 1
    int cur = 2;  // n = 2

    if (n < 3)
        return n;

    for (int i = 3; i <= n; i++)
    {
        int temp = prev + cur;
        prev = cur;
        cur = temp;
    }

    cout << cur;
}
