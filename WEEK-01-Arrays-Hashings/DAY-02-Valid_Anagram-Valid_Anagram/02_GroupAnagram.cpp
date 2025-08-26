/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]

Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Explanation:

There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
Example 2:

Input: strs = [""]

Output: [[""]]

Example 3:

Input: strs = ["a"]

Output: [["a"]]

 

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.
*/

/*
APPROACHES:

1. Brute-force (Time Limit Exceeded)
    If there's just one element in the list, return list of list of that element: [[element]]
    Interate over the list of strs (We will mark the elements as visited)
    If it is already visited (that means it was an anagram of a str earlier), so skip it
    create a temp list of strings
    insert the current element and assign this value to a string (to be used later)
    mark the element as visited
    started a nested loop
    if the current element is visted, skip it
    else check if it is an anagram of the base element
    if yes, add to the temp list and mark the current element as visited
    else continue
    once the inner nested loop is completed, add the temp list to the result list
    after all iterations, finally return the result.

    Time Complexity: O(n^2 * k) (where k is the length of each string which was given as 100)
                    = O(n^2 * 100) = O(n^2)
    Space Complexity:  O(n + m + p)
                        where, n = size of unordered map
                                m = size of temp list
                                p = size of result
                        = O(100 + m + p)
                        = O(m) (since, m <= p)




2. Sorting based
    create an unordered_map of string as key and vector<string> as value
    for each element in the original list
    sort the char of the element
    then for that sorted key, add to the vector the current element
    create the final result vector<vector<string>> iterate over the map
    keep on adding the second values (vector<string>) to final result and return the same

    Time complexity: O(n * k log k) [n = number of strings, k = length of string, k log k is for sorting]
    Space Complexity: O(n)




3. Frequency Hashing, avoids sorting
    Same as sorting 
    Except for that instead of sorting, it creates a freq list
    get frequency of each char in the current str
    create a key out of this freq list
    for this key, push the current element to the map
    Then finally add all the element from the map to the final list

    Time Complexity: O(n * k) [where, k is the length of a string = 100]
                    = O (n)
    Space Complexity: O(n + m) [where n ~ m]
                        = O(n)

*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Helper method - needed for burte-force
    bool checkAnagram(string str1, string str2) {
        if (str1.size() != str2.size())
            return false;

        unordered_map<char, int> m;
        for (char c : str1) m[c]++;
        for (char c : str2) m[c]--;

        for (auto& p : m) {
            if (p.second != 0)
                return false;
        }
        return true;
    }

    // main method
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // APPROACH 1: Brute-force
        // if (strs.size() == 1)
        //     return {{strs[0]}};

        // vector<vector<string>> res;
        // for (int i = 0; i < strs.size(); i++) {
        //     if (strs[i] == "-1") // already visited
        //         continue;

        //     vector<string> temp;
        //     temp.push_back(strs[i]);
        //     string base = strs[i]; 
        //     strs[i] = "-1"; // mark as visited

        //     for (int j = i + 1; j < strs.size(); j++) {
        //         if (strs[j] == "-1") continue;

        //         if (checkAnagram(base, strs[j])) {
        //             temp.push_back(strs[j]);
        //             strs[j] = "-1"; // mark as visited
        //         }
        //     }
        //     res.push_back(temp);
        // }
        // return res;


        // APPROACH 2: Sorting-based
        // unordered_map<string, vector<string>> m;
        // for(string s: strs){
        //     string base = s;
        //     sort(base.begin(), base.end());
        //     m[base].push_back(s);
        // }

        // vector<vector<string>> res;
        // for(auto& p : m)
        //     res.push_back(p.second);
        
        // return res;



        // APPROACH 3: Frequency Hashing, avoids sorting
        unordered_map<string, vector<string>> m;
        for(string s: strs){
            vector<int> freq(26, 0);
            for(char c: s) freq[c - 'a']++;

            string key = "";
            for(int i = 0; i < freq.size(); i++)
               key += to_string(freq[i]) + "#";
            m[key].push_back(s);
        }

        vector<vector<string>> res;
        for(auto& p : m)
            res.push_back(p.second);
        
        return res;
    }
};

int main() {
    Solution sol;
    vector<string> input = {"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> result = sol.groupAnagrams(input);

    for (auto& group : result) {
        cout << "[ ";
        for (auto& word : group) {
            cout << word << " ";
        }
        cout << "]\n";
    }

    return 0;
}
