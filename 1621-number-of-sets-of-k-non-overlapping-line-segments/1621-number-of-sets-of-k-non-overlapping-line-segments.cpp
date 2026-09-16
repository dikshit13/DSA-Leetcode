class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;
        vector<vector<long long>> dp(k + 1, vector<long long>(n, 0));
        vector<vector<long long>> open(k + 1, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i < n; i++) {
                open[j][i] = (open[j][i - 1] + dp[j - 1][i - 1]) % MOD;
                dp[j][i] = (dp[j][i - 1] + open[j][i]) % MOD;
            }
        }

        return dp[k][n - 1];
    }
};