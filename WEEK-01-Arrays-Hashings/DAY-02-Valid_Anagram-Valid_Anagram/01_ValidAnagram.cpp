/*
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

📖 Definition of Anagram:

An anagram is a word, phrase, or sequence of characters formed by rearranging the letters of another, using all the original letters exactly once and with the same frequency of each character.

Example 1:

Input: s = "anagram", t = "nagaram"

Output: true

Example 2:

Input: s = "rat", t = "car"

Output: false

 

Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.
 

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
*/


/*
APPROACHES:

1. Using unordered_map
    if the size of the strings does not match, return false.
    Create a map and store the frequency of each char of first string in the map
    Iterate over the other string and keep on decreasing the frequency for each element
    Iterate over the map and check if the freq. of each element is not 0 
    then definitely not an anagram
    else is an anagram

    Time complexity: O(n)
    Space complexity: O(n)
*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {

        // Approach 1: Unordered map
        unordered_map<char, int> m;
        for(char c: s) m[c]++;
        for(char c: t) m[c]--;

        for(auto& p: m){
            if(p.second != 0)
                return false;
        }
        return true;
    }
};

int main() {
    Solution sol;
    cout << boolalpha;
    cout << sol.isAnagram("listen", "silent") << endl; // true
    cout << sol.isAnagram("rat", "car") << endl;       // false
    return 0;
}
