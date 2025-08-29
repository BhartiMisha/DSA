/*
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Example 3:

Input: nums = [1,0,1,2]
Output: 3
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
*/


/*
APPROACHES

1. Sorting
    Just sort the elements of the list
    And check for the sequence

2. Priority queue
    IDEA: In priority queue, elements are dequed based on priority (maximum num). So this way we can arrange it backwards and keep on popping to get the sequence.
    LOGIC: Create a priority queue and store the all the elements of the list to this. 
    If the list is empty return 0
    We will use two int to store the current sequence and the max. sequence and one variable to store the prev number.
    Right before the loop we assign the topmost element to prev and value of 1 to each current sequence and max sequence
    We then iterate to the queue until it's empty
    we check if the current element is equal to prev element then skip
    if current element is one less than prev then increment curr_sequence, assign curr to prev and pop from the queue
    else if curr_seq is > max_seq, assign curr_seq to max_seq and update curr_seq to 1
    then again assign curr to prev and pop out from queue
    In the end, you'll have your max seq that you can return

    Time Complexity: O(n log n) -> n for total num and log n for push and pop operation
    Space Complexity: O(n)
*/


#include <iostream>
#include <queue>

using namespace std;

class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
            // APPROACH 2: Priority queue
            int globalCount = 0, curr_count = 0, prev = 0;
            priority_queue<int> pq;
            for(int i = 0; i < nums.size(); i++){
                pq.push(nums[i]);
            }
    
            if(nums.size() == 0)
                return 0;
            
            prev = pq.top();
            pq.pop();
            curr_count = 1, globalCount = 1;
            while(pq.size()){
                int curr = pq.top();
                if(curr == prev)
                {
                    pq.pop();
                    continue;
                }
                if(curr == prev-1){
                    curr_count++;
                    pq.pop();
                    prev = curr;
                    if(curr_count > globalCount){
                        globalCount = curr_count;
                    }
                } else{
                    prev = curr;
                    curr_count = 1;
                }
            }
        return globalCount;
        }
    };


int main() {
    Solution sol;

    // Example test case
    vector<int> nums = {100, 4, 200, 1, 3, 2};

    int result = sol.longestConsecutive(nums);

    cout << "Longest consecutive sequence length: " << result << endl;

    return 0;
}