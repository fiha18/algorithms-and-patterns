#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
    // Recursive function to calculate all subset sums for a given vector
    void subset_sum(vector<int>& ip, vector<int>& op, vector<int>& result) {
        if (ip.size() == 0) {
            // Calculate sum of current subset and add to result
            int sum = accumulate(op.begin(), op.end(), 0);
            result.push_back(sum);
            return;
        }
        
        // Process the last element in ip and store it temporarily
        int val = ip[ip.size() - 1];
        ip.erase(ip.begin() + (ip.size() - 1));
        
        // Include the last element in the subset
        op.push_back(val);
        subset_sum(ip, op, result);  // Recursive call after including element
        
        // Backtrack by removing the element
        op.pop_back();
        
        // Exclude the last element in the subset
        subset_sum(ip, op, result);  // Recursive call after excluding element
        
        // Re-add the element to restore ip's state for backtracking
        ip.push_back(val);
    }
    
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int half = n / 2;
        
        // Vectors to hold subset sums of both halves
        vector<int> sum1;
        vector<int> sum2;
        
        // Temporary output vectors to store subset elements during recursion
        vector<int> op1;
        vector<int> op2;
        
        // Divide nums into two halves and calculate subset sums
        vector<int> numsP(nums.begin(), nums.begin() + half);
        subset_sum(numsP, op1, sum1);  // First half subset sums
        
        vector<int> numsP2(nums.begin() + half, nums.end());
        subset_sum(numsP2, op2, sum2);  // Second half subset sums
        
        // Sort subset sums from the second half to enable binary search
        sort(sum2.begin(), sum2.end());
        int result = INT_MAX;
        
        // Iterate over each sum from the first half
        for (int i = 0; i < sum1.size(); i++) {
            int s1 = sum1[i];
            int l = 0, h = sum2.size() - 1;
            
            // Perform binary search in sorted subset sums of the second half
            while (l <= h) {
                int mid = l + (h - l) / 2;
                int sum = s1 + sum2[mid];
                
                // If exact match to goal, minimum difference achieved
                if (sum == goal) return 0;
                
                // Update result with minimum difference encountered
                result = min(result, abs(sum - goal));
                
                // Narrow down binary search based on current sum
                if (sum > goal) {
                    h = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        return result;
    }
};
