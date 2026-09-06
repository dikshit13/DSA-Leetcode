class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<long long> dp(m + 1);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = min(i, m); j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] = min(2147483647LL, dp[j] + dp[j - 1]);
                }
            }
        }

        return dp[m];
    }
};