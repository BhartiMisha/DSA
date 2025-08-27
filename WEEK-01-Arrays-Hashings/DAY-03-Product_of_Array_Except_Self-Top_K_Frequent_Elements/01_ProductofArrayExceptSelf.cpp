/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
 

Constraints:

2 <= nums.length <= 105
-30 <= nums[i] <= 30
The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
 

Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
*/

/*
APPROACHES:

1. Brute-force (Time Limit Exceeded)
    Iterate over the list
    Start another loop from 0th index
    Calculate product of all elements except for the current one (where i == j)
    Add the product to the resultant list

    Time Complexity: O(n ^ 2)
    Space Complexity: O(1)




2. Division method (not allowed by the question)
    Interate over the list of items
    For the items that are zero have a counter
    else calculate the product (combined_product) of items
    Start another loop (individual loop)
    If the count of zero is greater than 1 then definitely all items in result is zero
    else if the count of zero is exactly 1, then for the rest of the elements res will be zero and for the item zero, res will be product
    else current items product is combined_product divided by current product

    Time Complexity: O(n)
    Space Complexity: O(n)




3. Prefix-suffix method with extra space of O(n)
    IDEA: For any given element it's product will be = (prod of all prefix elements) * (prod of all suffix elements)
    CODE: Create three list (1- prefix, 2- suffix, and 3- result) and initialize with 1
    for prefix, iterate from 1st element to the last element
    prefix for any given element will be (prefix of prev ele) * (prev ele)
    for suffix, iterate from last but one (2nd last) element till 0th element
    suffix for any given element will be (suffix of last ele) * (last ele)
    Once the prefix and suffix for each element is calculated
    start a new loop from 0 to n (total count of original array)
    and for any given element, prod of other element will be (prefix of that element) * (suffix of that element)

    Time Complexity: O(n)
    Space Complexity: O(n)




4. Prefix-suffix method with no extra space
    IDEA: Same as approach 3 but with no extra space (space used only for result)
    CODE: Create just one result array with size as n and all values as 1.
    Calculate the prefix for each element and store in result
    i.e. iterate from index 1 to n and prefix for that element will be (pref of prev) * (prev)
    For suffix, start from last element and keep a right_product value as 1
    Now, for a given element final product will be (pref of curr) * (right_product)
    And since (pref of curr) is already present in res[i], so final product will be simply (res[i] * right_product)
    keep on multiplying curr_elemnt with right_product to get the suffix
    This way you get the result

    (SAME APPROACH BUT WELL WRITTEN WITH CHATGPT)
    Create a result array res of size n, initialize all with 1.
    Step 1: Build prefix product
        Go left to right.
        For each index i, prefix = (prefix of previous index) × (previous element).
        Store this prefix in res[i].
    Step 2: Apply suffix product
        Keep a variable right_product = 1.
        Go right to left.
        For each index i, final result = (res[i]) × (right_product).
        Update right_product = right_product × nums[i].
    Done → res now has product of array except self.

    Time Complexity: O(n)
    Space Complexity: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> productExceptSelf(vector<int>& nums) {
    // APPROACH 1: Brute-force
    // vector<int> res;
    // for(int i = 0; i < nums.size(); i++){
    //     int pro = 1;
    //     for(int j = 0; j < nums.size(); j++) {
    //         if(i != j) {
    //             pro *= nums[j];
    //         }
    //     }
    //     res.push_back(pro);
    // }
    // return res;



    // APPROACH 2: Division method
    // int product = 1;
    // int zeroCount = 0;
    // for (int i = 0; i < nums.size(); i++){
    //     if(nums[i] == 0) {
    //         zeroCount ++;
    //     } else {
    //         product *= nums[i];
    //     }
    // }

    // vector<int> res;
    // for(int i = 0; i < nums.size(); i++) {
    //     if(zeroCount > 1) {
    //         res.push_back(0);
    //     } else if(zeroCount == 1) {
    //         if(nums[i] == 0) {
    //             res.push_back(product);
    //         } else {
    //             res.push_back(0);
    //         }
    //     } else {
    //         res.push_back(product/nums[i]);
    //     }
    // }
    // return res;



    // APPROACH 3: prefix-suffix with space of O(n)
    // int n = nums.size();
    // vector<int> pre(n, 1), suff(n, 1), res(n);
    // for (int i = 1; i < n; i++){
    //     pre[i] = pre[i - 1] * nums[i - 1];
    // }

    // for (int i = n - 2; i >= 0; i--){
    //     suff[i] = suff[i + 1] * nums[i + 1];
    // }

    // for(int i = 0; i < n; i++){
    //     res[i] = pre[i] * suff[i];
    // }
    // return res;



    // APPROACH 4: prefix-suffix with O(1) space
    int n = nums.size();
    vector<int> res(n, 1);
    for(int i = 1; i < n; i++){
        res[i] = res[i - 1] * nums[i - 1];
    }
    int right = 1;
    for(int i = n - 1; i >= 0; i--){
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}

int main() {
    vector<int> nums = {1, 2, 3, 4};
    
    vector<int> result = productExceptSelf(nums);

    cout << "Result: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
