/*
Description
Design an algorithm to encode a list of strings to a single string. The encoded string is then decoded back to the original list of strings.

Please implement encode and decode

Example 1:

Input: ["neet","code","love","you"]

Output:["neet","code","love","you"]
Example 2:

Input: ["we","say",":","yes"]

Output: ["we","say",":","yes"]
Constraints:

0 <= strs.length < 100
0 <= strs[i].length < 200
strs[i] contains only UTF-8 characters.


Recommended
You should aim for a solution with O(m) time for each encode() and decode() call and O(m+n) space, where m is the sum of lengths of all the strings and n is the number of strings.
*/

/*
APPROACHES:

1. Brute-force
    Idea is to generate a key for each character and word and separate them out
    Logic:
    For encode, iterate over the list of elements
    For each element, iterate over the characters
    Get the ascii key and separate them by a symbol, say, "#"
    And separate each word with a symbol say "!!"

    During decode, iterate over the string
    Split the encoded string by !! → gives words (but in ASCII form).
    Split each word by # → gives ASCII values.
    Convert ASCII values back to characters

    Encode:
    Time Complexity: O(n*m)
    Space Complexity: O(1)

    Decode: 
    Time Complexity: O(n)
        where, n is the length of the string and each character of the string is visited only once
    Space Complexity: O(n)

*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

string encode(vector<string>& strs) {
    char specialChar = '#';
    string specialWord = "!!";
    string curr = "";

    for (int i = 0; i < strs.size(); i++) {
        string words_key = "";
        for (int j = 0; j < strs[i].size(); j++) {
            int asciVal = (int)strs[i][j];
            string asciValStr = to_string(asciVal);
            words_key += specialChar + asciValStr;
        }
        curr += specialWord + words_key;
    }
    return curr;
}


vector<string> decode(string str) {
    vector<string> res;
    string specialWord = "!!";
    char specialChar = '#';

    int i = 0;
    while (i < str.size()) {
        // skip specialWord prefix
        if (i + 1 < str.size() && str[i] == '!' && str[i+1] == '!') {
            i += 2;
            string word = "";

            string num = "";
            while (i < str.size() && !(i + 1 < str.size() && str[i] == '!' && str[i+1] == '!')) {
                if (str[i] == specialChar) {
                    if (!num.empty()) {
                        int asciiVal = stoi(num);
                        word.push_back((char)asciiVal);
                        num = "";
                    }
                } else {
                    num += str[i];
                }
                i++;
            }

            // last number check
            if (!num.empty()) {
                int asciiVal = stoi(num);
                word.push_back((char)asciiVal);
            }

            res.push_back(word);
        } else {
            i++;
        }
    }

    return res;
}


int main() {
    vector<string> strs = {"neet", "code", "true", "false"};

    string encoded = encode(strs);
    cout << "Encoded: " << encoded << endl;

    vector<string> decoded = decode(encoded);
    cout << "Decoded: ";
    for (auto &s : decoded) cout << s << " ";
    cout << endl;
}
