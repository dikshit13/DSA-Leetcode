class Solution {
public:
    vector<vector<int>> dp;

    int solve(int idx, int amount, vector<int>& coins) {
        if (amount == 0) return 1;
        if (idx == coins.size()) return 0;
        if (amount < 0) return 0;

        if (dp[idx][amount] != -1)
            return dp[idx][amount];

        int take = solve(idx, amount - coins[idx], coins);
        int skip = solve(idx + 1, amount, coins);

        return dp[idx][amount] = take + skip;
    }

    int change(int amount, vector<int>& coins) {
        dp.assign(coins.size(), vector<int>(amount + 1, -1));
        return solve(0, amount, coins);
    }
};