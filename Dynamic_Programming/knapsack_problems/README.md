# Knapsack Problem

## 0-1 Knapsack Problem

### Problem Statement
You are given weights and values of items to place in a knapsack of capacity `W`, aiming to maximize the total value without exceeding the capacity. Each item can only be chosen once.

- **Input**: Two integer arrays, `val[]` (values) and `wt[]` (weights) of `n` items, and an integer `W` representing knapsack capacity.
- **Output**: Maximum value subset of `val[]` with the total weight less than or equal to `W`.

### Solution Approaches

1. **Recursive Solution**  
   - **Time Complexity**: \(O(2^n)\)
   - **Space Complexity**: \(O(2^n)\)
   - **Explanation**: Using recursion, at each step, we decide to either include or exclude an item, generating all possible combinations of selected items. This approach is inefficient due to repeated calculations.

2. **Memoization (Top-Down Dynamic Programming)**  
   - **Time Complexity**: \(O(n * W)\)
   - **Space Complexity**: \(O(n * W) + O(n)\) (auxiliary stack space)
   - **Explanation**: We improve the recursive approach by storing already computed results in a 2D table, `dp[n][W]`, where `dp[i][j]` stores the maximum value obtainable with the first `i` items and weight capacity `j`. This avoids redundant calculations, significantly reducing computation time.

3. **Tabulation (Bottom-Up Dynamic Programming)**  
   - **Time Complexity**: \(O(n * W)\)
   - **Space Complexity**: \(O(n * W)\)
   - **Explanation**: We build a 2D table `dp[n+1][W+1]` where `dp[i][j]` represents the maximum value achievable with the first `i` items and capacity `j`. Starting from `i=0` and `j=0`, we iteratively fill the table by checking if each item can fit within the current capacity and updating the value accordingly. This approach is highly efficient and eliminates the need for recursion.

### Dynamic Programming Solutions for Related Problems

1. **Subset Sum**  
   - Find if there exists a subset of the array that sums up to a given target. Similar to the knapsack problem but with a goal of finding specific sums.

2. **Equal Sum Partition**  
   - Determine if an array can be partitioned into two subsets with equal sums. This problem reduces to a subset sum problem with target sum equal to half of the array's total sum.

3. **Count of Subset Sum**  
   - Count the number of subsets that sum up to a given target. The solution is based on modifying the knapsack approach to count all possible subsets with the target sum.

4. **Minimum Subset Sum Difference**  
   - Partition the array into two subsets such that the difference between their sums is minimized. Using a subset sum approach, we calculate the closest possible subset sum to half the total array sum.

5. **Target Sum**  
   - Assign `+` or `-` signs to elements to achieve a specific target sum. This problem is equivalent to finding subsets with a given difference and is solved using a subset count approach with the knapsack method.

6. **Number of Subsets with Given Difference**  
   - Given a difference value, count the number of ways to partition the array into two subsets with this exact difference. This is a variation of the subset sum count problem.
   
These problems share similarities with the knapsack problem and can be efficiently solved using dynamic programming approaches based on memoization and tabulation.
