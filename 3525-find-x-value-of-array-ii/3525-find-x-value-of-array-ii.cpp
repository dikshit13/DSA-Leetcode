class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int k;
    vector<Node> seg;

    Node merge(Node a, Node b) {
        Node res;
        res.prod = (a.prod * b.prod) % k;

        for (int i = 0; i < k; i++) {
            res.cnt[i] += a.cnt[i];
        }

        for (int i = 0; i < k; i++) {
            if (b.cnt[i]) {
                int r = (a.prod * i) % k;
                res.cnt[r] += b.cnt[i];
            }
        }

        return res;
    }

    void build(int idx, int l, int r, vector<int>& nums) {
        if (l == r) {
            seg[idx].prod = nums[l] % k;
            seg[idx].cnt[seg[idx].prod] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, nums);
        build(idx * 2 + 1, mid + 1, r, nums);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            seg[idx] = Node();
            seg[idx].prod = val % k;
            seg[idx].cnt[seg[idx].prod] = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, val);
        else
            update(idx * 2 + 1, mid + 1, r, pos, val);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(idx * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(idx * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(idx * 2, l, mid, ql, qr);
        Node right = query(idx * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();
        seg.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};