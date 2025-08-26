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

1. Brute-force
    If the size of the string does not match, return false.
    sort string 1
    sort string 2
    if string 1 == string true then return true
    else return false

    Time Complexity: O(n log n) [sorting]
    Space Complexity: O(1)




2. Using unordered_map
    if the size of the strings does not match, return false.
    Create a map and store the frequency of each char of first string in the map
    Iterate over the other string and keep on decreasing the frequency for each element
    Iterate over the map and check if the freq. of each element is not 0 
    then definitely not an anagram
    else is an anagram

    Time complexity: O(n)
    Space complexity: O(n)



3. Using frequency list (only in case if all the elements in the string is either upper case or lower case)
    Create a frequency list with size 26 (total alphabets) with all value as 0
    iterate over string 1 and increase the frequency of each char
    iterate over string 2 and decrease the frequency of each char
    iterate over the freq list and check the value
    if any value is not zero then the strings are not valid anagram.
    else they are valid anagrams.

    Time complexity: O(n)
    Space Complexity: O(n)
    
     
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>   // needed for sort()
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {

        // Approach 1: brute-force
        // if(! s.size() == t.size()) 
        //     return false;
        // sort(s.begin(), s.end());
        // sort(t.begin(), t.end());
        // return s == t;


        // Approach 2: Unordered map
        // unordered_map<char, int> m;
        // for(char c: s) m[c]++;
        // for(char c: t) m[c]--;

        // for(auto& p: m){
        //     if(p.second != 0)
        //         return false;
        // }
        // return true;


        // Approach 3: Using frequency list 
        int freq[26] = {0};

        for (char c : s) freq[c - 'a']++;
        for (char c : t) freq[c - 'a']--;

        for (int i = 0; i < 26; i++) {
            if (freq[i] != 0) return false;
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
