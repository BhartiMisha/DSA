/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
*/


/*
APPROACHES:

1. Brute-Force (TIME LIMIT EXCEEDED)
    IDEA: For any given bar at index i, the amount of water it can trap depends on the tallest bar to its left and the tallest bar to its right.
    The water above height[i] is determined by the smaller of these two walls (min(leftMax, rightMax)), because water will spill over the shorter side.
    Then subtract the height of the current bar (height[i]) to get the trapped water at that position.
    If the result is negative, we take 0 (because water can’t go below ground level).
    LOGIC:
    Create a result and assign value 0
    Traverse through the arary
        For any given height, get the max height on left and right.
        Now based on the idea, it can trap water in the minimum area between left and right max minus the current height (since current height is already occupied)
        Keep on adding to the result the min value between left and right max heights minus the current height. Also consider the fact that it cannot be a value less than zero
        So the final solution will be:
            max(0, min(leftMaxHeight, rightMaxHeight) - currHeight)
    return result

    Time Complexity: O(n^2)
    Space Complexity: O(1)
*/


#include <iostream>
#include <vector>
using namespace std;
class Solution {
    public:
        int trap(vector<int>& height) {
            int res = 0;
            for(int i = 0; i < height.size(); i++) {
                int leftMax = 0, rightMax = 0;
                for(int j = 0; j <= i; j++) {
                    leftMax = max(leftMax, height[j]);
                }
                for(int j = i + 1; j < height.size(); j++) {
                    rightMax = max(rightMax, height[j]);
                }
                res += max(0, min(leftMax, rightMax) - height[i]);
            } 
            return res;
        }
    };

    int main() {
    Solution sol;

    // Example input
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};

    int result = sol.trap(height);

    cout << "Total trapped water: " << result << endl;

    return 0;
}