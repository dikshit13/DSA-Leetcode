class Solution {
public:
    vector<string> ans;

    void solve(int index, string &digits, string &curr,
               vector<string> &mapping) {

        if(index == digits.size()) {
            ans.push_back(curr);
            return;
        }

        string letters = mapping[digits[index] - '0'];

        for(char ch : letters) {
            curr.push_back(ch);
            solve(index + 1, digits, curr, mapping);
            curr.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {

        if(digits.empty())
            return {};

        vector<string> mapping = {
            "", "",
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz"
        };

        string curr = "";

        solve(0, digits, curr, mapping);

        return ans;
    }
};