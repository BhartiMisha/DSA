/*
Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
Return k.
Custom Judge:

The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
If all assertions pass, then your solution will be accepted.
*/



/*
APPROACHES:

1. Brute-force
   IDEA:
      - Compare each element with the next one.
      - If a duplicate is found, shift all subsequent elements left.
      - Maintain a counter for unique elements.
   
   LOGIC:
      - Start at index 0.
      - For each element, check if it equals the next one.
      - If duplicate → shift array left and reduce size.
      - Else → move to next index.
      - Counter tracks unique count and is returned.

   Time Complexity: O(n^2)
   Space Complexity: O(1)


2. Set
   IDEA:
      - Use a set to automatically store only unique elements.
      - Overwrite the original array with these unique values.

   LOGIC:
      - Traverse array and insert all elements into a set.
      - Iterate through the set, writing its values back into the array from index 0.
      - Return the size of the set as the count of unique elements.

   Time Complexity: O(n)
   Space Complexity: O(n)


3. Two Pointers
   IDEA:
      - Maintain a subarray of unique elements within the same array.
      - Use two pointers: 
         - leftPtr → tracks the last position of the unique subarray
         - rightPtr → explores the array for the next unique element.

   LOGIC:
      - Initialize leftPtr at index 0 (last unique element’s position).
      - Traverse with rightPtr from index 1 onward.
      - If nums[rightPtr] != nums[leftPtr]:
            - increment leftPtr
            - assign nums[leftPtr] = nums[rightPtr]
      - Continue until end.
      - Return leftPtr + 1 as the number of unique elements.

   Time Complexity: O(n)
   Space Complexity: O(1)
*/




#include <iostream>
#include <set>
#include <vector>

using namespace std;


class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            // // APPROACH 1: BRUTE-FORCE
            // if(nums.size() == 0) {
            //     return 0;
            // }
            // int res = 1; // index for placing unique elements
            // for (int i = 1; i < nums.size(); i++) {
            //     if (nums[i] != nums[res - 1]) {   // new unique element
            //         nums[res] = nums[i];
            //         res++;
            //     }
            // }
            // return res;
            
            
            
            // // APPROACH 2: SET
            // set<int> uniqueElements;
            // for(int i = 0; i < nums.size(); i++) {
            //     uniqueElements.insert(nums[i]);
            // }
            // int i = 0;
            // for (int val : uniqueElements) {   // <-- fix: iterate instead of indexing
            //     nums[i++] = val;
            // }
            // return uniqueElements.size();



            // APPROACH 3: TWO POINTER
            int left = 0;
            int right = 0;
            int res = 1;
            while(right < nums.size() && left < nums.size()) {
                if(nums[left] == nums[right]) {
                    right++;
                } else {
                    nums[++left] = nums[right++];
                    res++;
                }
            }
            return res;
        }
    };


int main() {
    Solution sol;
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};

    int newLength = sol.removeDuplicates(nums);

    cout << "New length: " << newLength << endl;
    cout << "Array after removing duplicates: ";
    for (int i = 0; i < newLength; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}