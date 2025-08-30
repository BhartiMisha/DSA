/*
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2
*/

/*
APPRAOCHES:

1. Brute-force (TIME LIMIT EXCEEDED)
    IDEA: create all possible contiguous sub arrays and for each sub-array check if the element is equal to k or not
    LOGIC:
    Iterate from i = 0 till end of arr -> This will give the start of sub array
        Start inner iteration from ith position to end -> This will give the end of sub array
            Start one more iteration from start of sub array till end of sub array and calculate the sum
        If the sum equals k, increment the counter
    
    Time Complexity: O(n^3)
    Space Complexity: O(1)

    


2. Optimal Brute-Force
    Same as the previous one, but just that instead of having the third nested loop
    Create a sum for each outermost loop, and for the inner loop just keep on adding the next element in the subarray (coming from inner loop) to sum
    If sum equals k, add to result
    return result

    Time Complexity: O(n ^ 2)
    Space Complexity: O(1)




3. Prefix-sum with has maps
    Prefix Sum Concept:
        Let’s define:
        prefix[i] = nums[0] + nums[1] + … + nums[i]
        So, the sum of a subarray from i to j is:
            subarray(i,j) = prefix[j] − prefix[i−1]
            (for i > 0, else just prefix[j]).
        This is the key formula:
            subarray(i,j) = k ⟺ prefix[j] − prefix[i−1] = k
        Rearranging (for our problem's sake):
            prefix[i−1] = prefix[j] − k


    So, if at index j, we know prefix[j], we just need to know how many times prefix[j] - k has occurred before.
    That tells us how many subarrays ending at j have sum k.

    LOGIC:
    Maintain a hashmap (prefix_count) to store how many times each prefix sum has occurred.
    Initialize with {0: 1} → because before processing anything, we assume a "virtual prefix" of 0 has occurred once.
    Iterate through the array, computing cumulative prefix[j] on the fly.
    For each new prefix:
        Check if (prefix[j] - k) is in the hashmap.
            If yes → add its frequency to the result (because that many subarrays end here with sum k).
        Update hashmap with the new prefix[j].
    return result

    Time Complexity: O(n)
    Space Complexity: O(n)
*/


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        int subarraySum(vector<int>& nums, int k) {
            // APPROACH 1: BRUTE-FORCE
            // int res = 0;
            // for(int i = 0; i < nums.size(); i++){
            //     for( int j = i; j < nums.size(); j++) {
            //         int sum = 0;
            //         for(int k = i; k <= j; k++)
            //         {
            //             sum += nums[k];
            //         }
            //         if(sum == k)
            //             res++;
            //     }
            // }
            // return res;



            // // APPROACH 2: OPTIMAL BRUTE-FORCE
            // int res = 0;
            // for(int i = 0; i < nums.size(); i++){
            //     int sum = 0;
            //     for( int j = i; j < nums.size(); j++) {
            //         sum += nums[j];
            //         if(sum == k)
            //             res++;
            //     }
            // }
            // return res;



            // APPROACH 3: PREFIX-SUM WITH HASH MAPS
            unordered_map<int, int> prefixSum;
            prefixSum[0] = 1;

            int res = 0, totalSum = 0;
            for(int i = 0; i < nums.size(); i++) {
                totalSum += nums[i];
                int subarray_sum  = totalSum - k;
                if(prefixSum.find(subarray_sum) != prefixSum.end()) {
                    res += prefixSum[subarray_sum];
                }
                prefixSum[totalSum]++;
            }
            return res;   
        }
    };


int main() {
    Solution sol;

    // Test Case 1
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "Test Case 1 Output: " << sol.subarraySum(nums1, k1) << endl; 
    // Expected: 2

    // Test Case 2
    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    cout << "Test Case 2 Output: " << sol.subarraySum(nums2, k2) << endl; 
    // Expected: 2

    // Test Case 3
    vector<int> nums3 = {3, 4, 7, 2, -3, 1, 4, 2};
    int k3 = 7;
    cout << "Test Case 3 Output: " << sol.subarraySum(nums3, k3) << endl; 
    // Expected: 4 → [3,4], [7], [7,2,-3,1], [1,4,2]

    // Test Case 4
    vector<int> nums4 = {1};
    int k4 = 0;
    cout << "Test Case 4 Output: " << sol.subarraySum(nums4, k4) << endl; 
    // Expected: 0

    return 0;
}