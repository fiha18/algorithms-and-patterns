#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int minDifference(int arr[], int n) { 
        // Step 1: Calculate the total sum of all elements in the array
        int total_sum = 0;
        for (int i = 0; i < n; i++) {
            total_sum += arr[i];
        }

        // Step 2: Initialize a DP table where dp[i][j] represents whether 
        // a subset with sum j can be formed using the first i elements
        bool dp[n+1][total_sum+1];

        // Initialize first row to false (except dp[0][0]) since we can't 
        // form any sum with 0 elements except the sum of 0 itself
        for (int i = 0; i < total_sum + 1; i++) {
            dp[0][i] = false;
        }

        // Initialize first column to true since a sum of 0 can always be 
        // formed with any subset by choosing no elements
        for (int i = 0; i < n + 1; i++) {
            dp[i][0] = true;
        }

        // Step 3: Fill the DP table using the choice of including or 
        // excluding the current element
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < total_sum + 1; j++) {
                if (arr[i-1] <= j) {
                    // Include or exclude the element arr[i-1]
                    dp[i][j] = dp[i-1][j - arr[i-1]] || dp[i-1][j];
                } else {
                    // Exclude the element arr[i-1]
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        // Step 4: Find the largest possible subset sum (sum1) closest 
        // to total_sum / 2. This minimizes the difference between two subsets
        int sum1 = total_sum / 2;
        for (int i = sum1; i < total_sum + 1; i++) {
            if (dp[n][i] == true) {  // Check if subset with sum i is possible
                sum1 = i;
                break;
            }
        }

        // Step 5: Calculate the other subset sum (sum2) and return the absolute difference
        int sum2 = total_sum - sum1;
        return abs(sum1 - sum2);
    } 
};
