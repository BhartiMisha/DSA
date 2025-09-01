/*
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.

Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use the same element twice.

Your solution must use only constant extra space.

 

Example 1:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
Example 2:

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
Example 3:

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
 

Constraints:

2 <= numbers.length <= 3 * 104
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.
*/

/*
APPROACHES: 
1. Brute-force (Time Limit Exceeded)
    Create two nexted loops
    Check if the sum of the two elements is equal to the target
    If yes, return the indices of the two elements

    Time Complexity: O(n^2)
    Space Complexity: O(1)




2. Two pointers:
    IDEA: Since the array is sorted, we can use two pointers to find the two elements that add up to the target.
    decrementing the right pointer if the sum is greater than the target since it has larger values
    incrementing the left pointer if the sum is less than the target since it has smaller values
    Logic-
    Create two pointers- one at the start of the array and one at the end of the array
    Start a while loop with the condition that the right pointer is greater than the left pointer
    Get the sum of elements at right pointer and left pointer
    If the sum is equal to the target, return the indices + 1 (since question suggests 1-indexing) of the two elements
    If the sum is greater than the target, decrement the right pointer
    If the sum is less than the target, increment the left pointer

    Time Complexity: O(n)
    Space Complexity: O(1)
*/


#include <iostream>
# include <vector>

using namespace std;

class Solution {
    public:
        vector<int> twoSum(vector<int>& numbers, int target) {
            // // APPROACH 1: BRUTE-FORCE
            // vector<int> res;
            // for(int i = 0; i < numbers.size(); i++) {
            //     for(int j = i + 1; j < numbers.size(); j++) {
            //         if(numbers[i] + numbers[j] == target)
            //             return {i+1, j+1};
            //     }
            // }
            // return {-1, -1};



            // APPROACH 2: TWO POINTERS
            int left = 0, right = numbers.size() - 1;
            while(right > left) {
                int sum = numbers[right] + numbers[left];
                if(sum == target )
                    return {left+1, right+1};

                if(sum > target)
                    right--;
                else
                    left++;
            }
            return {-1, -1};
        }
    };


int main() {
    Solution sol;

    vector<int> numbers1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> res1 = sol.twoSum(numbers1, target1);

    cout << "Input: {2, 7, 11, 15}, target = 9" << endl;
    cout << "Output: [" << res1[0] << ", " << res1[1] << "]" << endl;

    vector<int> numbers2 = {1, 2, 3, 4, 4, 9, 56, 90};
    int target2 = 8;
    vector<int> res2 = sol.twoSum(numbers2, target2);

    cout << "Input: {1, 2, 3, 4, 4, 9, 56, 90}, target = 8" << endl;
    cout << "Output: [" << res2[0] << ", " << res2[1] << "  `]" << endl;

    vector<int> numbers3 = {1, 2, 3};
    int target3 = 10; // no valid pair
    vector<int> res3 = sol.twoSum(numbers3, target3);

    cout << "Input: {1, 2, 3}, target = 10" << endl;
    cout << "Output: [" << res3[0] << ", " << res3[1] << "]" << endl;

    return 0;
}