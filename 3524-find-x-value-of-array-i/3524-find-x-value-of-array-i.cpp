class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> ans(k, 0);
        vector<long long> cur(k, 0);

        for (int x : nums) {
            vector<long long> next(k, 0);
            int r = x % k;

            next[r]++;

            for (int rem = 0; rem < k; rem++) {
                if (cur[rem]) {
                    next[(rem * r) % k] += cur[rem];
                }
            }

            cur = next;

            for (int rem = 0; rem < k; rem++) {
                ans[rem] += cur[rem];
            }
        }

        return ans;
    }
};