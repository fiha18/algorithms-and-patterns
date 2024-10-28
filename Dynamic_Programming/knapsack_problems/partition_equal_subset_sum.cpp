#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // Calculate the sum of all elements in nums
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, it's impossible to partition into two equal subsets
        if (sum % 2 == 1) {
            return false;
        }
        
        int n = nums.size();
        int half_sum = sum / 2;

        // DP table where dp[i][j] indicates if we can achieve sum j with the first i elements
        bool dp[n + 1][half_sum + 1];

        // Initialize the DP table
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= half_sum; j++) {
                // No items means no sum (false) unless j is zero (empty subset case)
                if (i == 0) {
                    dp[i][j] = false;
                }
                // Sum zero can always be achieved with an empty subset
                if (j == 0) {
                    dp[i][j] = true;
                }
            }
        }

        // Fill the DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= half_sum; j++) {
                // Check if current element nums[i-1] can be part of subset for sum j
                if (nums[i - 1] <= j) {
                    // Choice: either include nums[i-1] or exclude it
                    dp[i][j] = dp[i - 1][j - nums[i - 1]] || dp[i - 1][j];
                } else {
                    // Exclude current element as it's larger than current sum target j
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // Result is whether we can partition into two subsets with half_sum
        return dp[n][half_sum];
    }
};
