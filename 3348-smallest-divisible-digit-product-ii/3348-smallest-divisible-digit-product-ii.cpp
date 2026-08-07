#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
    map<int, int> getPrimeCount(long long t) {
        map<int, int> count = {{2, 0}, {3, 0}, {5, 0}, {7, 0}};
        for (int p : {2, 3, 5, 7}) {
            while (t % p == 0) {
                count[p]++;
                t /= p;
            }
        }
        return count;
    }

    bool isValid(long long t) {
        long long temp = t;
        for (int p : {2, 3, 5, 7}) {
            while (temp % p == 0) temp /= p;
        }
        return temp == 1;
    }

    vector<int> getFactorCounts(const map<int, int>& pc) {
        int c2 = pc.at(2), c3 = pc.at(3), c5 = pc.at(5), c7 = pc.at(7);
        vector<int> digits(10, 0);
        
        digits[7] += c7; 
        digits[5] += c5; 
        
        digits[9] += c3 / 2; c3 %= 2;
        digits[8] += c2 / 3; c2 %= 3;
        
        if (c3 > 0 && c2 >= 1) {
            digits[6]++;
            c3--;
            c2--;
        }
        if (c3 > 0) {
            digits[3]++;
            c3--;
        }
        if (c2 == 2) {
            digits[4]++;
            c2 -= 2;
        } else if (c2 == 1) {
            digits[2]++;
            c2--;
        }
        return digits;
    }

    string construct(const vector<int>& digits) {
        string res = "";
        for (int d = 2; d <= 9; ++d) {
            res.append(digits[d], '0' + d);
        }
        return res;
    }

    map<int, int> getDigitPrimes(int d) {
        map<int, int> pc = {{2, 0}, {3, 0}, {5, 0}, {7, 0}};
        if (d == 2) pc[2] = 1;
        else if (d == 3) pc[3] = 1;
        else if (d == 4) pc[2] = 2;
        else if (d == 5) pc[5] = 1;
        else if (d == 6) pc[2] = 1, pc[3] = 1;
        else if (d == 7) pc[7] = 1;
        else if (d == 8) pc[2] = 3;
        else if (d == 9) pc[3] = 2;
        return pc;
    }

    bool isSubset(const map<int, int>& req, const map<int, int>& cur) {
        for (auto& [p, cnt] : req) {
            if (cur.at(p) < cnt) return false;
        }
        return true;
    }

public:
    string smallestNumber(string num, long long t) {
        if (!isValid(t)) return "-1";

        auto targetPrimes = getPrimeCount(t);
        auto minFactors = getFactorCounts(targetPrimes);
        
        int minLen = 0;
        for (int d = 2; d <= 9; ++d) minLen += minFactors[d];

        int n = num.length();
        if (minLen > n) {
            return construct(minFactors);
        }

        // Find the first zero index
        int firstZero = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                firstZero = i;
                break;
            }
        }

        // Check if num itself works (only possible if zero-free)
        if (firstZero == n) {
            map<int, int> curPrimes = {{2, 0}, {3, 0}, {5, 0}, {7, 0}};
            for (char c : num) {
                auto dp = getDigitPrimes(c - '0');
                for (auto& [p, cnt] : dp) curPrimes[p] += cnt;
            }
            if (isSubset(targetPrimes, curPrimes)) {
                return num;
            }
        }

        // We need to find a position `i` (0 <= i <= firstZero) to increment
        // If i == firstZero, the digit at firstZero was '0', so we must change it to something >= 1 (actually > 0, so 1..9)
        int limitIdx = min(firstZero, n - 1);
        
        map<int, int> prefixPrimes = {{2, 0}, {3, 0}, {5, 0}, {7, 0}};
        for (int i = 0; i < limitIdx; ++i) {
            auto dp = getDigitPrimes(num[i] - '0');
            for (auto& [p, cnt] : dp) prefixPrimes[p] += cnt;
        }

        for (int i = limitIdx; i >= 0; --i) {
            if (i < limitIdx) {
                auto dp = getDigitPrimes(num[i] - '0');
                for (auto& [p, cnt] : dp) prefixPrimes[p] -= cnt;
            }

            int startDigit = (i < firstZero) ? (num[i] - '0' + 1) : 1;
            for (int d = startDigit; d <= 9; ++d) {
                auto nextPrimes = prefixPrimes;
                auto dp = getDigitPrimes(d);
                for (auto& [p, cnt] : dp) nextPrimes[p] += cnt;

                map<int, int> rem;
                for (auto& [p, cnt] : targetPrimes) {
                    rem[p] = max(0, cnt - nextPrimes[p]);
                }
                
                auto neededFactors = getFactorCounts(rem);
                int neededLen = 0;
                for (int digit = 2; digit <= 9; ++digit) neededLen += neededFactors[digit];

                if (i + 1 + neededLen <= n) {
                    string res = num.substr(0, i) + to_string(d);
                    int fillOnes = n - res.length() - neededLen;
                    res.append(fillOnes, '1');
                    res += construct(neededFactors);
                    return res;
                }
            }
        }

        // If length needs to increase
        string res = "";
        res.append(n + 1 - minLen, '1');
        res += construct(minFactors);
        return res;
    }
};