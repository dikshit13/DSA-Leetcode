class Solution {
public:
    int strongPasswordChecker(string password) {

        int n = password.size();

        bool lower = false, upper = false, digit = false;

        for(char c : password)
        {
            if(islower(c)) lower = true;
            else if(isupper(c)) upper = true;
            else if(isdigit(c)) digit = true;
        }

        int missing = (!lower) + (!upper) + (!digit);

        vector<int> groups;

        for(int i = 0; i < n;)
        {
            int j = i;

            while(j < n && password[j] == password[i])
                j++;

            groups.push_back(j - i);

            i = j;
        }

        int replace = 0;

        for(int len : groups)
            replace += len / 3;

        if(n < 6)
            return max(missing, 6 - n);

        if(n <= 20)
            return max(missing, replace);

        int del = n - 20;

        int remain = del;

        for(int mod = 0; mod < 3; mod++)
        {
            for(int &len : groups)
            {
                if(remain == 0)
                    break;

                if(len < 3 || len % 3 != mod)
                    continue;

                int need = mod + 1;

                while(len >= 3 && remain >= need && len % 3 == mod)
                {
                    len -= need;
                    remain -= need;
                    replace--;
                }
            }
        }

        return del + max(missing, replace);
    }
};