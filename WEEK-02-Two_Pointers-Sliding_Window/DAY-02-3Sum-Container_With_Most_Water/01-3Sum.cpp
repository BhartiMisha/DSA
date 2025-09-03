/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
 

Constraints:

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/


/*
APPROACHES:

1. Brute-force (TIME LIMIT EXCEEDED)
    IDEA: create all possible triplets and check if the sum of the triplet is equal to 0
    LOGIC:
    Create a set to store the triplets (to avoid duplicates)
    Iterate from i = 0 till end of arr -> This will give the start of triplet
        Start inner iteration from i + 1 till end of arr -> This will give the start of second triplet
        Start another inner iteration from j + 1 till end of arr -> This will give the start of third triplet
        Check if the sum of the triplet is equal to 0
        If yes, sort the triplet and add the triplet to the result
    return the result in a vector form

    Time Complexity: O(n^3)
    Space Complexity: O(1)




2. Convert to 2Sum problem
    IDEA: we can convert this problem to 2Sum problem by fixing one element and then finding the other two elements that sum to 0
    Since, a + b + c = 0, we can say that a + b = -c
    So calculate the c as 0 - (a + b)
    LOGIC:
    Iterate from i = 0 till end of arr -> This will give the start of triplet
        Create an unordered_map to store the elements and their indices
        Start inner iteration from i + 1 till end of arr -> This will give the start of second triplet
        Calcualte remaining as 0 - (a + b)
        Check if the remaining is present in the map
        If yes, sort the triplet and add the triplet to the result
    return the result in a vector form

    Time Complexity: O(n^2 . log n) => log n is for sorting
    Space Complexity: O(n)
        



3. Two pointers
    IDEA: Fix one element and then use two pointers to find the other two elements that sum to 0
    LOGIC:
    Create a vector to store the triplets
    Sort the array, so that we can use two pointers to find the other two elements that sum to 0
    Iterate over the array - this fixes the first element of the triplet
        First ignore duplicates, i.e. if the current element is same as the previous element (only in case the current index > 0), skip it
        Initialize two pointers- one at the next index of the current element and one at the last index of the array
        Calculate the sum of the elements at the two pointers and the fixed element (from outer loop)
        If sum is equal to 0, add the triplet to the result
            Then skip all the duplicates of the second element of the triplet (the element at the first pointer)
            Then skip all the duplicates of the third element of the triplet (the element at the second pointer)
            increment the first pointer
            decrement the second pointer
        else if sum is less than 0, increment the first pointer
        else sum is greater than 0, decrement the second pointer
    return the result in a vector form

    Time Complexity: O(n^2)
    Space Complexity: O(1)

*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            // // APPROACH 1: BRUTE-FORCE
            // set<vector<int>> res;
            // int n = nums.size();
            // for(int i = 0; i < n; i++)
            // {
            //     for(int j = i + 1; j < n; j++)
            //     {
            //         for(int k = j + 1; k < n; k++)
            //         {
            //             if(nums[i] + nums[j] + nums[k] == 0)
            //             {
            //                 vector<int> triplet = {nums[i], nums[j], nums[k]};
            //                 sort(triplet.begin(), triplet.end()); // sort so {1,-1,0} and {-1,0,1} look same
            //                 res.insert(triplet);
            //             }
            //         }
            //     }
            // }
            // vector<vector<int>> ans(res.begin(), res.end());
            // return ans;



            // // APPROACH 2: CONVERT TO 2SUM PROBLEM
            // set<vector<int>> res;
            // for(int i = 0; i < nums.size(); i++) {
            //     unordered_map<int, int> num_to_index;
            //     for(int j = i + 1; j < nums.size(); j++){
            //         int rem = 0 - (nums[i] + nums[j]);
            //         if(num_to_index.find(rem) != num_to_index.end()){
            //             vector<int> triplet = {nums[i], nums[j], rem};
            //             sort(triplet.begin(), triplet.end());
            //             res.insert(triplet);
            //         }
            //         num_to_index[nums[j]] = j;
            //     }
            // }
            // vector<vector<int>> ans(res.begin(), res.end());
            // return ans;



            // APPROACH 3: TWO POINTERS
            vector<vector<int>> res;
            int n = nums.size();

            sort(nums.begin(), nums.end());

            for(int i = 0; i < n; i++) {
                if (i > 0 && nums[i - 1] == nums[i]) continue;

                int left = i + 1, right = n - 1;
                while(left < right) {
                    int sum = nums[i] + nums[left] + nums[right];
                    if(sum == 0) {
                        res.push_back({nums[i], nums[left], nums[right]});

                        // Ignore duplicates
                        while(left < right && nums[left] == nums[left+1]) left++;
                        while(left < right && nums[right] == nums[right-1]) right--;
                        
                        left++;
                        right--;
                    } else if(sum < 0) {
                        left++;
                    } else{
                        right--;
                    }
                }
            }
            return res;
        }
    };

int main() {
    Solution sol;

    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    vector<vector<int>> result = sol.threeSum(nums);

    cout << "Triplets that sum to 0 are:\n";
    for (auto& triplet : result) {
        cout << "[ ";
        for (int x : triplet) cout << x << " ";
        cout << "]\n";
    }

    return 0;
}