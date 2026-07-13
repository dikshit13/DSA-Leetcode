class Solution {
public:

    void solve(int index, vector<int>& candidates, int target,
               vector<int>& curr, vector<vector<int>>& ans)
    {
        if(target == 0)
        {
            ans.push_back(curr);
            return;
        }

        if(index == candidates.size() || target < 0)
            return;

        curr.push_back(candidates[index]);
        solve(index, candidates, target - candidates[index], curr, ans);
        curr.pop_back();

        solve(index + 1, candidates, target, curr, ans);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

        vector<vector<int>> ans;
        vector<int> curr;

        solve(0, candidates, target, curr, ans);

        return ans;
    }
};