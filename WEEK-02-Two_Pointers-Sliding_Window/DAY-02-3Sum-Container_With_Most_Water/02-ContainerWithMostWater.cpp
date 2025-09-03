/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.


Example 1: 
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
*/

/*
APPROACHES:

1. Brute-force (TIME LIMIT EXCEEDED)
    IDEA: Get all possible pairs of lines and calculate the area of the container
    LOGIC: 
    Create a res (will store the max value of the area found) and initialize it with INT_MIN
    Iterate over the array
        Start another iteration from an incremented index (i + 1)
            get the min height of the two heights
            calculate total water, i.e. min_height * (distance between the two) = min_height * (j - i)
            if the total water is greater than res, replace result.
    return result

    Time Complexity: O(n^2)
    Space Complexity: O(1)




2. Two pointer
    IDEA: Start with left at 0 and right at n-1, compute area each step, move the pointer with the smaller 
    height (since it limits area and bigger height will give bigger area),
    and keep track of the maximum until they meet.
    Intuition:
        Moving the taller line can never improve area, because the shorter one still limits it.
        Moving the shorter line gives a chance to increase the limiting height.
    LOGIC:
    Create a variable that will store the result and initialize it with INT_MIN (since it has to contain the max area)
    Set the left and the right pointers at extreme end
    Start the loop till left < right
        Get the min height of left and right
        Caluclate total_water/total_area that will be product of min_height and the distance between right and left
        Replace result with the max value between result and the total area calculated
        Now move the pointer left or right based on which height is small, if right's height is small, decrement the right pointer and vice versa.
    return the result
*/


#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
    public:
        int maxArea(vector<int>& height) {
            // // APPROACH 1: BRITE-FORCE
            // int res = INT_MIN;
            // for(int i = 0; i < height.size(); i++) {
            //     for(int j = i + 1; j < height.size(); j++) {
            //         int min_height = min(height[i], height[j]);
            //         int total_water = min_height * (j - i);
            //         res = max(total_water, res);
            //     }
            // }
            // return res;



            // APPROACH 2: TWO-POINTER
            int res = INT_MIN;
            int left = 0, right = height.size() - 1;
            while(left < right) {
                int min_height = min(height[left], height[right]);
                int total_water = min_height * (right - left);
                res = max(total_water, res);
                if(height[left] > height[right]) {
                    right--;
                } else {
                    left++;
                }
            }
            return res;
        }
    };

int main() {
    Solution sol;

    // Example input
    vector<int> height = {1,8,6,2,5,4,8,3,7};

    int result = sol.maxArea(height);

    cout << "Maximum water that can be contained: " << result << endl;

    return 0;
}