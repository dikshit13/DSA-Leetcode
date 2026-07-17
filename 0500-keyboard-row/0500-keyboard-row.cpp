class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        unordered_map<char, int> mp;

        string row1 = "qwertyuiop";
        string row2 = "asdfghjkl";
        string row3 = "zxcvbnm";

        for (char c : row1) mp[c] = 1;
        for (char c : row2) mp[c] = 2;
        for (char c : row3) mp[c] = 3;

        vector<string> ans;

        for (string word : words) {
            int row = mp[tolower(word[0])];
            bool ok = true;

            for (char c : word) {
                if (mp[tolower(c)] != row) {
                    ok = false;
                    break;
                }
            }

            if (ok)
                ans.push_back(word);
        }

        return ans;
    }
};