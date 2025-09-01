/*
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

 

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
 

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.
*/

/*
APPROACHES:
1. Brute-force:
    Create two variables one to store the new string and one to store the reversed string
    Iterate over the string
    if the character is alphanumeric then add lowercase of it to the new string
    if the character is not alphanumeric then skip it
    reverse the new string
    compare the new string and the reversed string
    if they are the same then return true
    else return false
    
    Time Complexity: O(n)
    Space Complexity: O(n)




2. Two Pointers:
    Create two pointers- one at the start of the string and one at the end of the string
    If the left charact is not aplhanumeric, increment the left pointer
    If the right character is not alphanumeric, decrement the right pointer
    If the left character is not equal to the right character, return false
    return true

    Time Complexity: O(n)
    Space Complexity: O(1)

*/


#include <iostream>
using namespace std;

class Solution {
    public:
        bool isPalindrome(string s) {
            // // APPROACH 1: BRUTE-FORCE
            // string reverse = "", orig = "";
            
            // for(int i = 0; i < s.size(); i++)
            // {
            //     if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))
            //     orig += tolower(s[i]);
            // }
    
            // for(int i = s.size() - 1; i >= 0; i--)
            // {
            //     if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))
            //     reverse += tolower(s[i]);
            // }
            // return orig == reverse;



            // APPROACH 2: TWO POINTERS
            int left = 0; 
            int right = s.size() - 1;
            while(left <= right) {
                if(!isalnum(s[left])) {
                    left++;
                    continue;
                } else if(!isalnum(s[right])) {
                    right--;
                    continue;
                } 
                if(tolower(s[left]) != tolower(s[right])){
                    cout << left << " " << right;
                    return false;
                }
                left++;
                right--;
            }
            return true;
        }
    };

int main() {
    Solution sol;

    string s1 = "A man, a plan, a canal: Panama";
    string s2 = "race a car";
    string s3 = "No lemon, no melon";

    cout << s1 << " -> " << (sol.isPalindrome(s1) ? "true" : "false") << endl;
    cout << s2 << " -> " << (sol.isPalindrome(s2) ? "true" : "false") << endl;
    cout << s3 << " -> " << (sol.isPalindrome(s3) ? "true" : "false") << endl;

    return 0;
}