class Solution {
public:
    struct Node {
        int l, r, w, idx;
    };

    struct State {
        long long score = 0;
        vector<int> ids;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Node> a(n);

        for (int i = 0; i < n; i++)
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};

        sort(a.begin(), a.end(), [](const Node& x, const Node& y) {
            if (x.l != y.l) return x.l < y.l;
            if (x.r != y.r) return x.r < y.r;
            return x.idx < y.idx;
        });

        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            int lo = i + 1, hi = n;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (a[mid].l > a[i].r)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            nxt[i] = lo;
        }

        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int k = 1; k <= 4; k++) {
            for (int i = n - 1; i >= 0; i--) {
                State skip = dp[k][i + 1];

                State take = dp[k - 1][nxt[i]];
                take.score += a[i].w;
                take.ids.push_back(a[i].idx);
                sort(take.ids.begin(), take.ids.end());

                if (take.score > skip.score ||
                    (take.score == skip.score && take.ids < skip.ids))
                    dp[k][i] = take;
                else
                    dp[k][i] = skip;
            }
        }

        return dp[4][0].ids;
    }
};