#include <bits/stdc++.h>
using namespace std;

class Solution {

    public:
    int perfectSum(int arr[], int n, int sum) {
        const int MOD = 1e9 + 7;  // Define modulus to handle large numbers

        // Initialize a 2D DP array where dp[i][j] represents the number of ways to get sum `j` using the first `i` elements.
        vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));

        // Base Case: If sum is 0, there's one way to achieve it (by selecting no elements)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        // Fill the DP table
        for (int i = 1; i <= n; i++) {  // Loop over each element
            for (int j = 0; j <= sum; j++) {  // Loop for each possible sum up to `sum`
                if (arr[i - 1] <= j) {  
                    // If the current element can be included in the sum `j`
                    // dp[i-1][j - arr[i-1]] represents including current element
                    // dp[i-1][j] represents excluding current element
                    dp[i][j] = (dp[i - 1][j - arr[i - 1]] + dp[i - 1][j]) % MOD;
                } else {
                    // If the current element is greater than `j`, it cannot be included
                    dp[i][j] = dp[i - 1][j] % MOD;
                }
            }
        }

        // Return the number of ways to get `sum` using all `n` elements
        return dp[n][sum];
    }
};
