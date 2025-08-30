/*
Given an integer array nums, find a subarray that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 

Constraints:

1 <= nums.length <= 2 * 104
-10 <= nums[i] <= 10
The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
*/

/*
APPROACHES:

1. Brute-force
    Start with declaring a variable to track the largest product and assign the first element to it
    Start the iteration from first to last element
        Create a current product val and assign 1 to it
        Start a nested loop from ith to last position (the two loops are to get all possible combination of sub arrays)
            change product to product * current element [jth element]
            if this product is greater than largestProduct, update the largestProduct to this product
    return largest product

    Time Complexity: O(n ^ 2)
    Space Complexity: O(n)

*/


#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        int maxProduct(vector<int>& nums) {
            // // APPROACH 1: BRUTE-FORCE
            // int largestProduct = nums[0];
            // for(int i = 0; i < nums.size(); i++) {
            //     int pro = 1;
            //     for(int j = i; j < nums.size(); j++) {
            //         pro *= nums[j];
            //         largestProduct = largestProduct > pro ? largestProduct : pro;
            //     }
            // }
            // return largestProduct;
            
        }
    };


int main() {
    Solution sol;

    vector<int> nums1 = {2, 3, -2, 4};
    cout << "Max Product of nums1: " << sol.maxProduct(nums1) << endl; 
    // Expected: 6 (subarray [2,3])

    vector<int> nums2 = {-2, 0, -1};
    cout << "Max Product of nums2: " << sol.maxProduct(nums2) << endl; 
    // Expected: 0 (subarray [0])

    vector<int> nums3 = {-2, 3, -4};
    cout << "Max Product of nums3: " << sol.maxProduct(nums3) << endl; 
    // Expected: 24 (subarray [-2,3,-4])

    vector<int> nums4 = {0, 2};
    cout << "Max Product of nums4: " << sol.maxProduct(nums4) << endl; 
    // Expected: 2 (subarray [2])

    return 0;
}