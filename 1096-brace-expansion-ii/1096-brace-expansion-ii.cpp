class Solution {
public:
    set<string> merge(set<string>& a, set<string>& b) {
        set<string> res;
        for (auto &x : a)
            for (auto &y : b)
                res.insert(x + y);
        return res;
    }

    set<string> parse(string& s, int& i) {
        set<string> res, cur;

        while (i < s.size() && s[i] != '}') {
            if (s[i] == '{') {
                i++;
                set<string> temp = parse(s, i);
                i++;
                
                if (cur.empty())
                    cur = temp;
                else
                    cur = merge(cur, temp);
            }
            else if (s[i] == ',') {
                for (auto &x : cur)
                    res.insert(x);
                cur.clear();
                i++;
            }
            else {
                set<string> temp = {string(1, s[i])};
                if (cur.empty())
                    cur = temp;
                else
                    cur = merge(cur, temp);
                i++;
            }
        }

        for (auto &x : cur)
            res.insert(x);

        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> ans = parse(expression, i);
        return vector<string>(ans.begin(), ans.end());
    }
};