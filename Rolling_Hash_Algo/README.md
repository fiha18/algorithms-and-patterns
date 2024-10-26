# Rolling Hash - Rabin Karp Algorithm

## Using Simple Hashing Function 

### Rolling Hash

The Rolling Hash technique enables efficient substring searching by computing a hash for a "window" of characters in the text and sliding this window to the next position without recalculating the entire hash. Here’s a step-by-step example of the Rolling Hash approach.

#### Example Walkthrough

Consider the following scenario:
- **Pattern:** `"abc"`
- **Text:** `"abcdefabc"`
- **Hash Function:** Each letter is assigned a numerical value: `a = 1, b = 2, ..., z = 26`.
- **String Hash Calculation:** The sum of the character values.

#### Steps

1. **Calculate Hash for Pattern**
   - For pattern `"abc"`, hash is `1 + 2 + 3 = 6`.

2. **Calculate Hash for the First Window in Text**
   - First window (first 3 characters of text) is `"abc"`, with hash `1 + 2 + 3 = 6`.

3. **Compare Hashes**
   - Pattern hash (`6`) matches the first window's hash (`6`), so we check the characters:
     - Characters match (`abc = abc`), so the pattern is found at position `0`.

4. **Move to the Next Window (Rolling Hash)**
   - Slide the window one character to the right: New window is `"bcd"`.
   - Adjust hash by removing the leftmost character (`a` value `1`) and adding the new rightmost character (`d` value `4`):
     - `New hash = 6 - 1 + 4 = 9`

5. **Compare Hashes Again**
   - Pattern hash (`6`) does not match new window's hash (`9`), so skip character checks and move to the next window.

6. **Continue Sliding the Window**
   - Update hash for each new window:
     - **"cde":** `9 - 2 (b) + 5 (e) = 12`
     - **"def":** `12 - 3 (c) + 6 (f) = 15`
   - None of these hashes match the pattern hash.

7. **Reach the End of the Text**
   - Final window is `"abc"`.
   - Update hash: `15 - 4 (d) + 1 (a) = 6`
   - Hash matches pattern hash, and characters match, so the pattern is found again at position `6`.

#### Summary
The pattern `"abc"` was found at positions `0` and `6` in `"abcdefabc"`. By using a rolling hash, we efficiently updated the hash as the window moved, avoiding full recalculations for each position.


## Rolling Hash Algorithm with Enhanced Hash Function and Modulo 1000007

The Rolling Hash technique efficiently computes a hash for a "window" of characters in the text and slides this window without fully recalculating the hash each time. Here, we use a more complex hash function with powers of 26 and a modulo of 1000007 to keep hash values manageable.

#### New Hash Function

In this example:
- **Pattern:** `"abc"`
- **Text:** `"abcdefabc"`
- **Hash Function:** Each letter is given a positional multiplier in powers of 26, and the hash is taken modulo 1000007.

#### Steps

1. **Calculate Hash for Pattern**
   - Pattern is `"abc"`.
   - Hash calculation uses powers of 26:
     \[
     *Hash of pattern* = (1 *times* 26^2 + 2 *times* 26^1 + 3 *times* 26^0) *mod* 1000007
     \]

   Breaking it down:
   - \( 1 *times* 26^2 = 676 \)
   - \( 2 *times* 26^1 = 52 \)
   - \( 3 *times* 26^0 = 3 \)
   - Total hash = \( 676 + 52 + 3 = 731 \)
```c++
int hash = 0;  
int windowSize = 3;
for(int i = 0; i < windowSize ; i++)
	{
		hash = (hash*26 + (input[i] - 'a' + 1))%p;
	}
```
2. **Calculate Hash for First Window in Text**
   - The first window in the text `"abc"` has the same characters as the pattern, so:
     \[
     *Hash of first window* = (1 *times* 26^2 + 2 *times* 26^1 + 3 *times* 26^0) *mod* 1000007 = 731
     \]

3. **Compare Hashes**
   - Pattern hash (`731`) matches the first window's hash (`731`), so we proceed to check characters:
     - Characters match exactly (`abc = abc`), indicating the pattern is found at position `0`.

4. **Move to the Next Window (Rolling Hash)**
   - *take refernece from below rolling hash with number for more details how it moves from 112 to 121*
   - Slide the window to the right to the next substring, `"bcd"`.
   - Update the hash without recalculating entirely:
     - Remove leftmost character (`a`), which is \( 1 *times* 26^2 = 676 \).
     - Shift the remaining characters and add the new character (`d` with value `4`).
   - Adjusted hash:
     \[
     *New hash* = ((731 - 676) *times* 26 + 4) *mod* 1000007
     \] 
   - Calculations:
     - \( 731 - 676 = 55 \)
     - \( 55 *times* 26 + 4 = 1430 + 4 = 1434 \)
   - New hash for `"bcd"` is `1434`.
```c++
#define p 1000007

vector<int> rollingList;

int windowSize = 3;
for(int j = windowSize ; j < inputSize; j++)
	{
        
		hash = ((hash - rollingList[windowSize-1] * (input[j - windowSize] - 'a' + 1))%p + p)%p; 
		hash = (hash*26 + (input[j] - 'a' + 1))%p;
		if(map.find(hash) != map.end())
		{
			for(auto startIdx : map[hash])
			{
				string temp = input.substr(startIdx,windowSize);
				string curr = input.substr(j - windowSize + 1,windowSize);
				if(temp.compare(curr) == 0)
				{
					pattern = temp;
					return true;
				}
			}
		}
    }
```
5. **Compare Hashes Again**
   - Pattern hash (`731`) does not match new window hash (`1434`), so move to the next window without further character checks.

6. **Continue Sliding the Window**
   - Adjust hash for each new window:
     - For `"cde"`: Remove `b` (value `2 *times* 26^1 = 52`), add `e` (value `5`).
     - For `"def"`: Remove `c` (value `3 *times* 26^0 = 3`), add `f` (value `6`).
   - Repeat hash comparisons until the entire text is covered.

7. **End of Text**
   - At the end, the hash matches the pattern hash again at position `6`, confirming the pattern occurs at both positions `0` and `6` in `"abcdefabc"`.

#### Summary
Using a rolling hash with powers of 26 and modulo 1000007, we efficiently update hashes without recalculating them entirely, identifying pattern positions in the text with minimal overhead.


### Rolling Hash Example with Numbers

Given a numerical list `112123123` and using a rolling hash function with base power `10`:

**First Window (Initial Hash)**: `"112"`
- Calculate hash: \( 1 *times* 10^2 + 1 *times* 10^1 + 2 *times* 10^0 = 112 \)

**Slide to the Next Window (Rolling Hash)**
- Move to the next substring, `"121"`.
- Update the hash by removing the leftmost character (`1`), shifting the remaining values, and adding the new character (`1`).

- Adjusted hash:
    \[
        *New hash* = ((112 - 1 *times* 10^2) *times* 10 + 1) = (112 - 100) *times* 10 + 1 = 12 *times* 10 + 1 = 121
    \]

**Continue Sliding**
- For the next window `"212"`, repeat:
- Remove the leftmost `1`, shift, and add the next character `2`.

**Example Summary**: 
- Each step slides the window, updates the hash without recalculating, and allows efficient tracking across the list.


## Questions 
1. https://leetcode.com/problems/longest-duplicate-substring/description/