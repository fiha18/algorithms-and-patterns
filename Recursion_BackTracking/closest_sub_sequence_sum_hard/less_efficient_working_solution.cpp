#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int mid = n / 2;
        
        // Vectors to store all subset sums of the two halves
        vector<int> S1;
        vector<int> S2;
        
        // Split input vector into two halves
        vector<int> op1;
        vector<int> numsP(nums.begin(), nums.begin() + mid);
        solve(numsP, op1, S1);  // Calculate all subset sums for the first half
        
        vector<int> numsP2(nums.begin() + mid, nums.end());
        solve(numsP2, op1, S2);  // Calculate all subset sums for the second half
        
        // Sort the subset sums of the second half for binary search
        sort(S2.begin(), S2.end());
        int ans = INT_MAX;
        
        // Use each sum from the first half and binary search in the second half
        for (int i = 0; i < S1.size(); i++) {
            int s = S1[i];
            int l = 0;
            int r = S2.size() - 1;
            
            // Binary search in the sorted list of subset sums (S2) to find the closest sum to `goal`
            while (l <= r) {
                int mid = l + (r - l) / 2;
                int sum = s + S2[mid];
                
                // If exact match to goal, return 0 as it's the minimum possible difference
                if (sum == goal) return 0;
                
                // Update answer with the closest sum found so far
                ans = min(ans, abs(sum - goal));
                
                // Adjust binary search range based on current sum comparison to goal
                if (sum > goal) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }    
            }
        }
        return ans;
    }

    // Recursive function to generate all subset sums
    void solve(vector<int>& input, vector<int>& output, vector<int>& result) {
        if (input.size() == 0) {
            int sum = accumulate(output.begin(), output.end(), 0);
            result.push_back(sum);  // Store the subset sum in result
            return;
        }
        
        // Choose to include the first element in the subset
        output.push_back(input[0]);
        vector<int> ip(input.begin() + 1, input.end());
        solve(ip, output, result);  // Recursive call after including element
        
        // Backtrack by removing the last added element
        output.pop_back();
        
        // Choose to exclude the first element in the subset
        solve(ip, output, result);  // Recursive call after excluding element
    }
};
