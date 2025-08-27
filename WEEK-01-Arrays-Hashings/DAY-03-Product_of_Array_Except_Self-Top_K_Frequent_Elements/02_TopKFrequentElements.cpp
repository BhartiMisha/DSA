/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2

Output: [1,2]

Example 2:

Input: nums = [1], k = 1

Output: [1]

Example 3:

Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

Output: [1,2]

 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.
 

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/


/*
APPROACHES:

1. Brute-force
    Calculate freq of each element and add it to a map (key = element, val = freq)
    Create a vector<pair<int, int>> and store all elements of the map to this
    now sort the vector against second element (frequency)
    create a resultant list
    iterate over the sorted vector from 0 to k and add the elements to the resultant list
    return the list

    Time Complexity: O(n + n log n) = O(n log n); (n log n) is for sort
    Spae Complexity: O(n)




2. Using priority queue (Hash maps and priority queue (min-heap))
    IDEA: If you add any element to the priority queue, the top element will be the one with maximum value.
    CODE: Calculate freq of each element and add it to a map (key = element, val = freq)
    create a priority queue<pair<int, int>>
    iterate over the map and add teh elements to the priority queue
    iterate from 0 to k and keep on adding top element of priority queue to the res and pop in the same iteration

    Time Complexty: O([n log n] + [k log n]) = O(n log n); since n >= k
        where, n log n is to add elements to the queue
                k log n  => each extraction (pop) operation takes O(log n) time, and we do this k times
    Space Complexity: O(n)



3. Using Bucket sort
    IDEA: Frequency of an element can never be more than n (if all elements are the same).
    So we can create a "bucket" array of size n+1, where bucket[i] stores all elements that appear exactly i times.
    Then we iterate from the highest possible frequency (n) down to 1 and collect elements until we have k.
    CODE: Calculate freq of each element and add it to a map (key = element, val = freq)
    Create a bucket of vector<vector<int>> of size n + 1 (this is to store all elements [list/vector] of freq. i in ith position)
    Iterate over the map, and for each frequency (value from key-val pair of the map) add key to the list at the position value (which is basically the frequency)
    Now, iterate over the bucket from last position (n not n+1, since the size is n+1 and in case of reverse traversal we always start from size-1)
    the limit of the iteration should be- the res vector size is less than k and i >= 0 
    Now add to the list of elements of bucket[i] in the result list and if result.size() == k just break from there
    return the result list

    Time Complexity: O(n)
    Space COmplexity: O(n)
*/


#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    // APPROACH 1: Brute-force
    // unordered_map<int, int> freq;
    // for(int i = 0; i < nums.size(); i++){
    //     freq[nums[i]]++;
    // }

    // vector<pair<int, int>> ls(freq.begin(), freq.end());
    // sort(ls.begin(), ls.end(), [](auto &a, auto &b){
    //     return a.second > b.second;
    // });

    // vector<int> res;
    // for(int i = 0; i < k; i++){
    //     res.push_back(ls[i].first);
    // }
    // return res;



    // APPROACH 2: Using priority queue (Hash maps and priority queue (min-heap))
    // unordered_map<int, int> freq;
    // for(int i = 0; i < nums.size(); i++){
    //     freq[nums[i]]++;
    // }

    // priority_queue<pair<int, int>> pq;
    // for(auto& i: freq){
    //     pq.push({i.second, i.first});
    // }

    // vector<int> res;
    // for(int i = 0; i < k; i++){
    //     res.push_back(pq.top().second);
    //     pq.pop();
    // }
    // return res;



    // APPROACH 3: Using Bucket sort
    unordered_map<int, int> freq;
    for(int i = 0; i < nums.size(); i++){
        freq[nums[i]]++;
    }

    int n = nums.size();
    vector<vector<int>> bucket(n + 1);
    for(auto& i: freq){
        bucket[i.second].push_back(i.first);
    }

    vector<int> res;
    for(int i = n; i >= 0 && res.size() < k ; i--)
    {
        for(auto& j: bucket[i]){
            res.push_back(j);
            if(res.size() == k)
                break;
        }
    }
    return res;
}

int main() {
    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;

    vector<int> ans = topKFrequent(nums, k);
    cout << "Top " << k << " frequent elements: ";
    for (int num : ans) cout << num << " ";
    cout << endl;
}

