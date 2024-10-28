# Subset Sum Closest to Goal with Meet-in-the-Middle Approach

## Problem Description

Given an integer array `nums` and an integer `goal`, find the minimum absolute difference between the `goal` and the sum of any subset of `nums`. The subset can be empty.

### Key Concepts

1. **Subset Sum**: All possible subset sums for an array can be calculated recursively.
2. **Meet in the Middle**: We split `nums` into two halves, find all subset sums of each half, and then use a binary search to find the closest possible sum to `goal`.

---

## Solution Overview

### Brute Force Approach
A brute-force approach would generate all subsets and compute their sums, comparing each to `goal`. However, this is computationally infeasible for larger inputs as it has an exponential time complexity, \( O(2<sup>n</sup>) \).

### Meet-in-the-Middle Approach
We improve efficiency by:
1. Splitting the array into two halves.
2. Calculating all subset sums for each half.
3. Sorting one half’s subset sums and using binary search to quickly find the subset combination closest to `goal`.

This approach effectively reduces the time complexity to \( O(2<sup>(n/2)</sup> * log(2<sup>(n/2)</sup>)) \).

---

## Code Explanation

### Code 1 (Less Efficient)
**(Runtime - 2546 ms Beats - 5.88% & Memory - 688.56 MB Beats - 5.59%)**

1. **Subset Sum Calculation**: Uses a `solve` function that recursively builds all subset sums by including or excluding each element from the subset. This solution manipulates the input vector by erasing and creating **new vectors** at each recursive call, making it less memory efficient.
2. **Binary Search**: After computing all subset sums, the sums of the second half (`S2`) are sorted to allow binary search, enabling efficient closest-sum calculations against `goal`.
   
### Code 2 (More Efficient)
**(Runtime - 597 ms Beats - 73.53% & Memory - 84.94 MB Beats - 34.87%)**

1. **Efficient Subset Sum Calculation**: Uses a `subset_sum` function that backtracks after **adding or removing elements**, maintaining the original vector. This approach avoids new memory allocations, improving efficiency.
2. **Binary Search Optimization**: Similarly, sorts one half’s subset sums and performs binary search, achieving the closest match to `goal`.

---

## Time Complexity Analysis

For both solutions:
- **Subset Sum Calculation**: Generates all subsets for each half, taking \( O(2<sup>(n/2)</sup>) \) time.

- **Binary Search**: Sorting a half’s subset sums takes \( O(2<sup>(n/2)</sup> * log (2<sup>(n/2)</sup>)) = O(2<sup>(n/2)</sup> * (n/2)) \).

  
Thus, the overall complexity for both solutions is approximately \( O(2<sup>(n/2)</sup> * log 2<sup>(n/2)</sup>) \), making it feasible for large inputs with \( n = 40 \).

---

## Conclusion

The **Meet-in-the-Middle** approach drastically reduces time complexity compared to a brute-force method, allowing efficient solutions for large input sizes. 

- **Code 1** demonstrates a straightforward implementation but lacks memory efficiency.
- **Code 2** uses in-place recursion, making it better suited for larger data.

Both solutions yield the minimum absolute difference to `goal`, leveraging binary search to optimize subset matching.
