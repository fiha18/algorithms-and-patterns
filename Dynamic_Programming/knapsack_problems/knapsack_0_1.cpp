#include<bits/stdc++.h>
using namespace std;

class Solution
{
    public:
    // Declaring a 2D array to store intermediate results for memoization approach
    int dp[1002][1002];
    
    // Function to return the maximum value that can be put in a knapsack of capacity W
    int knapSack(int W, int wt[], int val[], int n) 
    { 
        // Uncomment below line to use memoization approach
        // memset(dp, -1, sizeof(dp));
        // return memo_dp(W, wt, val, n);

        // Using tabulation approach as default
        return knapsack_tabulation(W, wt, val, n);
    }
    
    // Memoization approach for knapsack problem
    // This approach uses top-down DP by recursively calculating values
    int memo_dp(int W, int wt[], int val[], int n) {
        // Base case: No items left or knapsack capacity is 0
        if (n == 0 || W == 0) {
            return 0;
        }
        
        // Check if value has already been calculated
        if (dp[n][W] != -1) return dp[n][W];
        
        // Case 1: Include current item if its weight is within current capacity W
        if (wt[n - 1] <= W) {
            return dp[n][W] = max(
                val[n - 1] + memo_dp(W - wt[n - 1], wt, val, n - 1), // Include item
                memo_dp(W, wt, val, n - 1) // Exclude item
            );
        }
        // Case 2: Exclude the item if its weight is more than the current capacity W
        else if (wt[n - 1] > W) {
            return dp[n][W] = memo_dp(W, wt, val, n - 1);
        }
        return 0;
    }

    // Tabulation approach for knapsack problem
    // This approach uses bottom-up DP with an iterative table-filling method
    int knapsack_tabulation(int W, int wt[], int val[], int n) 
    { 
        // Initializing DP table where dp[i][j] represents the maximum value
        // achievable with the first i items and capacity j
        int dp[n + 1][W + 1];
        
        // Initialize the first row and column to 0
        // A knapsack with 0 capacity or no items can hold a value of 0
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= W; j++) {
            dp[0][j] = 0;
        }
        
        // Fill the DP table in a bottom-up manner
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= W; j++) {
                // Check if the current item's weight is within the current capacity j
                if (wt[i - 1] <= j) {
                    // Choose the maximum of including or excluding the current item
                    dp[i][j] = max(
                        val[i - 1] + dp[i - 1][j - wt[i - 1]], // Include item
                        dp[i - 1][j] // Exclude item
                    );
                } else {
                    // If current item's weight is more than the capacity, exclude it
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        // The final result is the maximum value achievable with n items and capacity W
        return dp[n][W];
    }
};
