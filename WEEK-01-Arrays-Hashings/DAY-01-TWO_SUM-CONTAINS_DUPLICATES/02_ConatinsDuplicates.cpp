/*
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

 

Example 1:

Input: nums = [1,2,3,1]

Output: true

Explanation:

The element 1 occurs at the indices 0 and 3.

Example 2:

Input: nums = [1,2,3,4]

Output: false

Explanation:

All elements are distinct.

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]

Output: true

 

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
*/


/*
APPROACH
1. Brute-force [Issues- Time Limit Exceeded]
    Traverse through the list
    start a nested loop from current + 1 position
    If a match is found, return true
    after the end of both the loops return false (will only reach here if no duplicates present)
    
    Time complexity: O(n^2)
    Space: O(1)

2. Use of sets (since sets contains only unique elements)
    Assign elements of the list to a set
    if the length of set and list matches then no duplicates
    else duplicates present
    
    Time complexity: O(n)
    Space complexity: O(n)

3. Maps 1 [Same like sets]
    Add all elements to a map
    check the size of the map
    if size of list != size of map then definitely a duplicqate present
    else no duplicates
    
    Time complexity: O(n)
    Space complexity: O(n)

4. Maps 2 [Most optimized]
    Create a frequency map [key: element, val: frequency of the element]
    traverse over the list
    if freq of an element is already present (should be greater than 0) then duplicates present so return true
    else increase frequency of the element
    
    Time complexity: O(n)
    Space complexity: O(n)
*/

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        // 1. Brute-force
        // for (int i = 0; i < nums.size(); i++) {
        //     for (int j = i + 1; j < nums.size(); j++) {
        //         if (nums[i] == nums[j]) {
        //             return true; // duplicate found
        //         }
        //     }
        // }
        // return false; // no duplicates




        // 2. Use of sets
        // set<int> uniqueElements;
        // for (int num : nums) {
        //     uniqueElements.insert(num);
        // }
        // return uniqueElements.size() != nums.size();




        // 3. Maps 1 [Same like sets]
        // map<int, int> elementMap;
        // for (int num : nums) {
        //     elementMap[num]++;
        // }
        // return elementMap.size() != nums.size();




        // 4. Maps 2- Most optimized
        map<int, int> freq;  // key -> frequency
        for (int i = 0; i < (int)nums.size(); i++) {
            if (freq[nums[i]] > 0) {
                return true; // duplicate found
            }
            freq[nums[i]]++;
        }
        return false; // no duplicates
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {1, 2, 3, 1};

    // Call function
    bool result = sol.containsDuplicate(nums);

    // Print output
    if (result) {
        cout << "Contains duplicate" << endl;
    } else {
        cout << "No duplicates" << endl;
    }

    return 0;
}
