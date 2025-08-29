/*
Given a string s, find the length of the longest substring without duplicate characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
*/


/*
APPROACHES:

1. Brute-Force:
    Keep a counter for longest count
    Iterate over each element in the string
    create a freq map to calculate and store the freq of each element for the next loop and a current seq counter
    start an inner loop from (i + 1)th element
    Keep on increasing the freq
    If the freq is more than 1, break from the nested loop
    else keep on incrementing the curr_seq_counter
    Replace the longest count with max of curr_seq_counter and longest_counter
    return longest_counter

    Time Complexity: O(n ^ 2)
    Space Complexity: O(n)




2. Sliding Window with Set
    Create a set that will store elements of the current window
    Create a variable to remember/take care of left index and a variable to store the longest seq (initialize with 0)
    Iterate over the string
    if the current element is found in the set then remove one element from the left till there's no element left in the sliding window that matches the current element
    in the inner while loop (to remove all the elements till the duplicate is found on left), also keep on increasing the left index as you're removing that element
    Out of the loop, add the current element to the set
    the longest sequence value will be max of longest 
    Finally out of the main loop, return longest

    Time Complexity: O(n) -> Each element is visited maximum twice (one when found next when removing)
    Space Complexity: O(n)
*/

#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
        //    // APPROACH 1: BRUTE-FORCE
        //    int longest = 0; 
        //    for(int i = 0; i < s.size(); i++) {
        //         unordered_map<char, int> freq;
        //         int j = 0;
        //         int curr_len = 1;
        //         freq[s[i]]++;
        //         for(int j = i + 1; j < s.size(); j++) {
        //             freq[s[j]]++;
        //             if(freq[s[j]] > 1)
        //             {
        //                 break;
        //             } else {
        //                 curr_len++;
        //             }
        //         }
        //         longest = max(curr_len, longest);
        //    }
        //    return longest;



        // APPROACH 2: SLIDING WINDOW WITH SET
        set<char> charSet;
        int left = 0, longest = 0;
        for(int right = 0; right < s.size(); right++)
        {
            char curr = s[right];
            while(charSet.find(curr) != charSet.end()){
                charSet.erase(s[left]);
                left++;
            }
            charSet.insert(curr);
            longest = max(longest, right - left + 1);
        } 
        return longest;
        }
    };

int main() {
    Solution sol;

    // Test cases
    string s1 = "abcabcbb";
    string s2 = "bbbbb";
    string s3 = "pwwkew";
    string s4 = "";

    cout << "Input: " << s1 << " -> " << sol.lengthOfLongestSubstring(s1) << endl;
    cout << "Input: " << s2 << " -> " << sol.lengthOfLongestSubstring(s2) << endl;
    cout << "Input: " << s3 << " -> " << sol.lengthOfLongestSubstring(s3) << endl;
    cout << "Input: (empty string) -> " << sol.lengthOfLongestSubstring(s4) << endl;

    return 0;
}