class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutes;

        for (string &t : timePoints) {
            int h = stoi(t.substr(0, 2));
            int m = stoi(t.substr(3, 2));
            minutes.push_back(h * 60 + m);
        }

        sort(minutes.begin(), minutes.end());

        int ans = INT_MAX;

        for (int i = 1; i < minutes.size(); i++) {
            ans = min(ans, minutes[i] - minutes[i - 1]);
        }

        ans = min(ans, 1440 - minutes.back() + minutes.front());

        return ans;
    }
};