class Solution {
public:
    int longestPalindrome(string s) {

        unordered_map<char, int> freq;

        for(char ch : s)
        {
            freq[ch]++;
        }

        int length = 0;
        bool oddFound = false;

        for(auto it : freq)
        {
            if(it.second % 2 == 0)
            {
                length += it.second;
            }
            else
            {
                length += it.second - 1;
                oddFound = true;
            }
        }

        if(oddFound)
            length++;

        return length;
    }
};