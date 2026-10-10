class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        vector<int> diff(n);

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
        }

        sort(diff.begin(), diff.end(), greater<int>());

        for (int i = 0; i < n && k > 0; i++) {
            if (i == n - 1 || diff[i] > diff[i + 1]) {
                long long next = (i == n - 1) ? 0 : diff[i + 1];
                long long count = i + 1;
                long long need = (diff[i] - next) * count;

                if (k >= need) {
                    k -= need;
                    for (int j = 0; j <= i; j++) {
                        diff[j] = next;
                    }
                } else {
                    long long dec = k / count;
                    long long rem = k % count;

                    for (int j = 0; j <= i; j++) {
                        diff[j] -= dec;
                        if (j < rem) {
                            diff[j]--;
                        }
                    }

                    k = 0;
                }
            }
        }

        long long ans = 0;

        for (int d : diff) {
            ans += 1LL * d * d;
        }

        return ans;
    }
};