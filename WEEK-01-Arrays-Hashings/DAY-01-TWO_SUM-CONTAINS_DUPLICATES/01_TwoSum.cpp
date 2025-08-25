/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
 

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?

*/


/*
APPROACHES:

1. Brute Force Method:
    - Use two nested loops to check all possible pairs
    - Outer loop iterates through each element
    - Inner loop checks all subsequent elements for the complement
    - If sum equals target, return the indices
    - If no pair found, return empty vector
    
    Time Complexity: O(n²)
    Space Complexity: O(1)

2. Hash maps
    Create a map to store key-val pair
    where, key is element of list and val is its index
    iterate over the list (not map) one by one
    if |target - curr_ele| is present in the map
    then get the value (index) of each of the element (remaining/complement and current element of the list) 
    else return an empty list

    Time complexity: O(n)
    Space complexity: O(n)
*/

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        // Brute-force
        // vector<int> ans;
        // for (int i = 0; i < nums.size(); i++) {
        //     for (int j = i + 1; j < nums.size(); j++) {
        //         if (nums[i] + nums[j] == target) {
        //             ans.push_back(i);
        //             ans.push_back(j);
        //             return ans;
        //         }
        //     }
        // }
        // return ans;



        // Hash map method
        unordered_map<int, int> store; // value -> last index
        for (int i = 0; i < (int)nums.size(); ++i) {
            store[nums[i]] = i;
        }

        // Check each element's complement
        for (int i = 0; i < nums.size(); ++i) {
            int rem = target - nums[i];
            auto it = store.find(rem);
            if (it != store.end() && it->second != i) {
                return {i, it->second};
            }
        }
        return {}; // no pair found
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    // Call the function
    vector<int> result = sol.twoSum(nums, target);

    // Print result
    if (!result.empty()) {
        cout << "Indices: " << result[0] << ", " << result[1] << endl;
    } else {
        cout << "No two sum solution found." << endl;
    }

    return 0;
}
