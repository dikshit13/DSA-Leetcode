class Solution {
public:
    int divide(int dividend, int divisor) {

        if(dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long dvd = llabs((long long)dividend);
        long long dvs = llabs((long long)divisor);

        long long quotient = 0;

        while(dvd >= dvs)
        {
            int shift = 0;

            while(dvd >= (dvs << (shift + 1)))
            {
                shift++;
            }

            dvd -= (dvs << shift);
            quotient += (1LL << shift);
        }

        if((dividend < 0) ^ (divisor < 0))
            quotient = -quotient;

        return (int)quotient;
    }
};