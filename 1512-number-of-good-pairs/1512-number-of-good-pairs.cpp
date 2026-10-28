class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        vector<pair<int, int>> pairs;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] == nums[j]) {
                    pairs.push_back({i, j});
                }
            }
        }

        return pairs.size();
    }
};