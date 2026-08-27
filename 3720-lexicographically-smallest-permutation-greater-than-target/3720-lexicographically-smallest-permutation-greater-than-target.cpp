class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int cnt[26] = {};

        for (char c : s)
            cnt[c - 'a']++;

        string ans;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            int x = target[i] - 'a';

            if (cnt[x] > 0) {
                ans += target[i];
                cnt[x]--;
            } else {
                for (int c = x + 1; c < 26; ++c) {
                    if (cnt[c] > 0) {
                        ans += char('a' + c);
                        cnt[c]--;

                        for (int k = 0; k < 26; ++k)
                            ans += string(cnt[k], char('a' + k));

                        return ans;
                    }
                }
                break;
            }
        }

        for (int i = (int)ans.size() - 1; i >= 0; --i) {
            cnt[ans.back() - 'a']++;
            ans.pop_back();

            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; ++c) {
                if (cnt[c] > 0) {
                    ans += char('a' + c);
                    cnt[c]--;

                    for (int k = 0; k < 26; ++k)
                        ans += string(cnt[k], char('a' + k));

                    return ans;
                }
            }
        }

        return "";
    }
};