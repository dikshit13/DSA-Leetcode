#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
string lexPalindromicPermutation(string s, string target) {
vector<int> cnt(26);


    for (char c : s)
        cnt[c - 'a']++;

    int odd = 0, mid = -1;

    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2) {
            odd++;
            mid = i;
        }
    }

    if (odd > 1)
        return "";

    int n = s.size();
    int m = n / 2;

    vector<int> halfCnt(26);

    for (int i = 0; i < 26; i++)
        halfCnt[i] = cnt[i] / 2;

    string half = target.substr(0, m);

    if (canBuild(half, halfCnt)) {
        string candidate = buildPalindrome(half, mid);
        if (candidate > target)
            return candidate;
    }

    for (int i = m - 1; i >= 0; i--) {
        vector<int> used(26);
        bool valid = true;

        for (int j = 0; j < i; j++) {
            int c = half[j] - 'a';
            used[c]++;

            if (used[c] > halfCnt[c]) {
                valid = false;
                break;
            }
        }

        if (!valid)
            continue;

        int cur = half[i] - 'a';

        for (int c = cur + 1; c < 26; c++) {
            if (used[c] < halfCnt[c]) {
                string res = half.substr(0, i);
                res += char('a' + c);

                vector<int> remaining = halfCnt;

                for (int j = 0; j < i; j++)
                    remaining[half[j] - 'a']--;

                remaining[c]--;

                for (int k = 0; k < 26; k++)
                    res += string(remaining[k], char('a' + k));

                return buildPalindrome(res, mid);
            }
        }
    }

    return "";
}


private:
bool canBuild(const string& half, const vector<int>& halfCnt) {
vector<int> used(26);


    for (char c : half) {
        used[c - 'a']++;

        if (used[c - 'a'] > halfCnt[c - 'a'])
            return false;
    }

    return true;
}

string buildPalindrome(const string& half, int mid) {
    string res = half;

    if (mid != -1)
        res += char('a' + mid);

    string rev = half;
    reverse(rev.begin(), rev.end());

    return res + rev;
}


};
