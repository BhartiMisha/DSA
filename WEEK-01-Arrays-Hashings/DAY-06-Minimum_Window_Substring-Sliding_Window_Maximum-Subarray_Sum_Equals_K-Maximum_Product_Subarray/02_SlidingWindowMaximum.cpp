/*
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

-----------------------------------
Better Explanation (SELF ADDED):
We’re given:
    An array of integers nums.
    A window size k.
A sliding window of size k starts at the left end of the array and moves one step at a time to the right.
At each step, the window "sees" only the k elements inside it.
We need to return a list of the maximum element in each window as the window slides across the array.
-----------------------------------

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/


/*
APPROACHES: 

1. Brute-Force (TIME LIMIT EXCEEDED)
    Set left as 0 (Starting position of the window)
    Set right as k - 1 (End of the window)
    Iterate over the main array from left to right (where, left < nums.size() && right < nums.size() && right - left + 1 == k)
    In each iteration, get the maximum number and add that to the resultant array.
    Keep on incrementing left and right index in each iteration.

    Time Complexity: O(m * k)
                Where, m = size of the array (this is to iterate over the array)
                        k = size of the window provided - this is to calculate the max number of that window
    Space Complexity: O(n)




2. Deque
    IDEA: Deque is a data structure where elements can be popped out from both front and back ends and same is the case with insertion.
        So the idea is basically to store the index of the elements in the decreasing order (left to right- ex: | 5 | 4 | 3 | 2 | 1 |) of the elements of the array.
        And pop out from the front side if the index is out of the current sliding window.
        Otherwise, pop from the back if the element at the current index is greater than (or equal to) the elements at indices present in the deque.
        This ensures that the deque always contains potential maximum candidates for the current window, and the front of the deque is the maximum element’s index.

        Why storing index and not number-
            1. With direct numbers we won't be able to tell if it is out of bound or not, but with index we can directly say that.
                The sliding window moves forward by index.
                Example:
                    nums = [1,3,-1,-3,5,3,6,7], k = 3
                At i = 3, the window should only cover indices [1,2,3].
                If the deque had only numbers, you couldn’t tell whether the 1 belongs to index 0 (out of window) or somewhere else.
                Storing indices makes it easy: just check dq.front() < i - k + 1.
            2. Handling duplicates - Suppose array is [1,1,1,1] with k=2.
                If deque stores only numbers, it will look like [1,1,1,1] — you can’t distinguish which index each 1 came from.
                But with indices, you know exactly where each 1 is in the array.
    LOGIC:
    Create a deque to store the indices
    Create a resultant list
    Iterate over the list of numbers
    For each element:
        Out of bound check: Since the window slides by one each time, if the index at the front of the deque is out of the current window, remove it.
        Maintain decreasing order: Remove all indices from the back of the deque whose element is less than or equal to the current element (because they will never be the maximum while the current element is in the window).
        Insert the index of the current element into the deque.
        Valid window formed: If the current index is large enough to form a complete window (i ≥ k - 1), append the element at the index present at the front of the deque (that’s the max of current window) to the resultant list.
    Return the resultant list

    Time Complexity: O(n) => Each element contributes at most 1 push + 1 pop = 2 operations. Across n elements → at most 2n operations. 
    Space Complexity: O(n)
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution {
    public:
        int get_max(vector<int>& nums, int l, int r) {
            int max_ = INT_MIN;
            for(int i = l ; i <= r; i++){
                max_ = max_ > nums[i] ? max_ : nums[i] ;
            }
            return max_;
        }
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {

            // // APPROACH 1: BRUTE-FORCE
            // vector<int> res;
            // int left = 0, right = k - 1;
            // while(right < nums.size() && left < nums.size() && (right - left + 1) == k) {
            //     int max_ = get_max(nums, left, right);
            //     res.push_back(max_);
            //     right++;
            //     left++;
            // }
            // return res;



            // APPROACH 2: DEQUE
            deque<int> dq;
            vector<int> ans;
            for(int i = 0; i < nums.size(); i++) {
                // remove the out of bound element (the element left behind i.e. not part of the sliding window) from deque
                if(!dq.empty() && dq.front() <=  i-k)
                    dq.pop_front();

                // Since we're storing the elements in decreasing order and pushing the same from the back, we kepe on removing the elements that are less than the current element, since that is not in need right now
                while(!dq.empty() && nums[dq.back()] < nums[i])
                    dq.pop_back();

                // Since all the elements less than current element has been removed, we can push the current index in
                dq.push_back(i);
                // Add to the ans only when atleast one sliding window is found
                if(i >= k - 1)
                    ans.push_back(nums[dq.front()]);
            }
            return ans;
        }
    };

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    // Call function
    vector<int> result = sol.maxSlidingWindow(nums, k);

    // Print output
    cout << "Max in each sliding window of size " << k << ": ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}