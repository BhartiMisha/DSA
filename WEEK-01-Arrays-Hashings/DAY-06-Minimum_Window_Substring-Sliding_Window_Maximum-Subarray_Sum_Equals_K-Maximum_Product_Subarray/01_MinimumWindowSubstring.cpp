/*
Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 

Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
 

Follow up: Could you find an algorithm that runs in O(m + n) time?
*/


/*
APPROACHES:

1. Brute-force-ish - sliding window [TIME LIMIT EXCEEDED]
    If t is larger than s, return "" immediately since no valid window can exist.
    Build a frequency map global_ for all characters in t. This map represents how many times each character must appear in any valid window
    Start with a window size equal to t.size()
    Set left = 0 and right = t.size() - 1
    Extract the first substring curr_substr = s.substr(left, right - left + 1) as the current window.
    Maintain variables res (to store the result substring) and final_count (to track the length of the smallest valid window found).
    Iterate until the window reaches the end of the string
        Check validity of the current window (write another function to check this- This function checks if all characters of t are present in the current substring with at least the required frequency.)
        If the window is valid
        Compare the window size with the best result so far.
        If it is the first valid substring or smaller than the previous best, update res and final_count.
        Then, attempt to shrink the window from the left by doing left++ and updating curr_substr.
        If the window is invalid, Expand the window by moving right++ and update curr_substr.
    Continue this process of shrinking and expanding until the window covers the entire string.
    Return the smallest valid substring res found during the process.

    Time Complexity: O((n ^ 2) * n) = O(n ^ 3)
        Where, O(n ^ 2) is the worst case scenario for different window check
        And O(n) is the check to see if all elements of t is part of the current substring

    Space Complexity: O(n)




2. Sliding window optimal
    The idea is again the sliding window to slide from left and right
    Optimized thing is that to check if the char in t is present in the current substring
    we will maintain two hash maps and two variables
    One hash map to store all char of t and their frequency, another one to check the char and freq coming from the substring
    One variable to check the need (total count of elements of the hash map of t) and one to check the total elements that the substring have currently
    Eventually there will be two checks- 
    1. If the current element is present in both the maps or not
    2. If the have and need is equal
    Idea of doing this is that if curr element is present in both the maps with same frequency and have == need then it is a substring of s with all char of t in it.
    In other cases, we keep on sliding the window and incrementing "have" value when count of that char is same in both the maps
    And decrease if current element is present in countT hash map and count of element in current hash map is less than count of that element in countT hash map

    LOGIC:
    If t.size() > s.size() return ""
    Create two maps- countT and window.
    Create a left variable for left index of window, result count as INT_MAX, a pair to store resultant index pair(left, right) initialize it with {-1, -1}
    Now add the freq of all char of t in countT map
    create a "have" with value 0 and "need" equals size of countT map
    Iterate from first element of s (this interation counter will be the right and will keep on incrementing the right index of the window)
    Increase counter of current element in the window
    if the window[curr_ele] == countT[curr_ele], increment the have counter
    an internal loop (while) to keep on decreasing the window from left till have == need (This is to keep on eliminating elements from left window)
        In this, we first update the result (only in case the curr length is smaller than previously stored result)
        from window (that stores current substr freq) we decrease the freq of leftmost string
        if leftmost string is found in countT map and leftmost element count in window map < leftmost element count in countT map then decrement "have"
        We finally increment the left index with 1.
    Finally return the resultant substring if any was found else and empty string.

    Time Complexity: O(m + n) => m to iterate over t and n to iterate over s (since max we'll go over each element of s twice- one to add another to remove, so its O(2n) but we write it as O(n))
    Space Complexitu: O(n)
*/


#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
    public:
        bool check_t_presence(string substr, unordered_map<char, int> freq) {
            for(int i = 0; i < substr.size(); i++) {
                if(freq.find(substr[i]) != freq.end()) {
                    freq[substr[i]]--;
                }
            }
    
            for(auto& f: freq){
                if(f.second > 0)
                    return false;
            }
            return true;
        }
    
        string minWindow(string s, string t) {
            // // APPROACH 1: BRUTE_FORCE_ISH - SLIDING WINDOW
            // if(t.size() > s.size())
            //     return "";
    
            // int left = 0, min_substr_size = t.size();
            // int right = min_substr_size - 1;
            // unordered_map<char, int> global_;
    
            // string res;
            // int final_count = 0;
            // string curr_substr = s.substr(left, right - left + 1);
    
            // for(int i = 0; i < t.size(); i++) {
            //     global_[t[i]]++;
            // }
    
            // while(left < s.size() && right < s.size() && left <= right) {
            //     int subStr_has_all_t_ele = check_t_presence(curr_substr, global_);
            //     if(subStr_has_all_t_ele) {
            //         int curr_size = curr_substr.size();
            //         if(final_count == 0 || final_count > curr_size) {
            //             final_count = curr_size;
            //             res = curr_substr;
            //         }
            //         // shrink from left
            //         left++;
            //         if(left <= right) {
            //             curr_substr = s.substr(left, right - left + 1);
            //         }
                    
            //     } else {
            //         right++;
            //         if(right < s.size()) {
            //             curr_substr = s.substr(left, right - left + 1);
            //         }
            //     }
            // }
            // return res;



            // APPROACH 2: SLIDING WINDOW OPTIMAL
            if(t.size() > s.size())
                return "";
            unordered_map<char, int> countT, window;
            int resCount = INT_MAX, left = 0;
            pair<int, int> res = {-1, -1};

            for(char c: t) {
                countT[c]++;
            }

            int have = 0, need = countT.size();
            for(int right = 0; right < s.size(); right++) {
                char curr_char = s[right];
                window[curr_char]++;

                if(window[curr_char] == countT[curr_char])
                    have++;
                
                while(have == need) {
                    if(right - left + 1 < resCount) {
                        resCount = right - left + 1;
                        res = {left, right};
                    }
                    char leftMost_char = s[left];
                    window[leftMost_char]--;
                    if(countT.find(leftMost_char) != countT.end() && window[leftMost_char] < countT[leftMost_char]) {
                        have--;
                    }
                    left++;
                }
            }
            return resCount == INT_MAX ? "" : s.substr(res.first, resCount);
        }
    };

    int main() {
        Solution sol;
        
        string s = "ADOBECODEBANC";
        string t = "ABC";
    
        string ans = sol.minWindow(s, t);
    
        if(ans.empty())
            cout << "No valid window found" << endl;
        else
            cout << "Smallest window containing \"" << t << "\" is: " << ans << endl;
    
        return 0;
    }