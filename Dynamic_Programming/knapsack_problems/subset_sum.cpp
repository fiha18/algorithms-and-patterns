#include<bits/stdc++.h>
using namespace std;

class Solution {   
public:
    // DP table for memoization approach
    int dp[101][10001];
    
    // Main function to check if a subset with the given sum exists
    bool isSubsetSum(vector<int> arr, int sum) {
        // Uncomment below for memoization
        // memset(dp, -1, sizeof(dp));  // Initialize dp array with -1
        // int n = arr.size();          // Size of array
        // return memo_dp(arr, sum, n); // Call memoized recursive function
        
        // Tabulation approach (default in this case)
        return isSubsetSum_tabulation(arr, sum);
    }
    
    // Memoization approach for subset sum problem
    bool memo_dp(vector<int>& arr, int sum, int n) {
        // Base case: if sum is 0, we can always achieve it with an empty subset
        if (sum == 0) return true;
        
        // Base case: if no elements left and sum is not 0, return false
        if (n == 0) return false;
        
        // Return cached result if already computed
        if (dp[n][sum] != -1) return dp[n][sum];
        
        // Include or exclude the current element based on its value relative to the sum
        if (arr[n-1] <= sum) {
            // Store result of including or excluding the element in dp table
            dp[n][sum] = memo_dp(arr, sum - arr[n - 1], n - 1) || memo_dp(arr, sum, n - 1);
        } else {
            // Exclude the current element as it exceeds the sum
            dp[n][sum] = memo_dp(arr, sum, n - 1);
        }
        
        return dp[n][sum];
    }

    // Tabulation (Bottom-Up) approach for subset sum problem
    bool isSubsetSum_tabulation(vector<int> arr, int sum) {
        int n = arr.size(); // Size of the array
        bool dp[n + 1][sum + 1];
        
        // Initialization: a sum of 0 can be achieved by choosing no elements
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        
        // If there are no elements, we can't achieve any positive sum
        for (int i = 1; i <= sum; i++) {
            dp[0][i] = false;
        }
        
        // Fill the dp table using a bottom-up approach
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= sum; j++) {
                if (arr[i - 1] <= j) {
                    // If element is less than or equal to the current sum, include or exclude it
                    dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
                } else {
                    // Exclude the element if it exceeds the current sum
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        // Result: Whether we can achieve the target sum with all elements considered
        return dp[n][sum];
    }
};
