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
