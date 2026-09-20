class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            int rev = 'z' - s[i] + 1;
            ans += rev * (i + 1);
        }

        return ans;
    }
};