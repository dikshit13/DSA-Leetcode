class Solution {
public:

    bool canSplit(vector<int>& nums, int k, long long limit)
    {
        int subarrays = 1;
        long long sum = 0;

        for(int num : nums)
        {
            if(sum + num <= limit)
            {
                sum += num;
            }
            else
            {
                subarrays++;
                sum = num;
            }
        }

        return subarrays <= k;
    }

    int splitArray(vector<int>& nums, int k) {

        long long left = *max_element(nums.begin(), nums.end());
        long long right = 0;

        for(int num : nums)
            right += num;

        while(left < right)
        {
            long long mid = left + (right - left) / 2;

            if(canSplit(nums, k, mid))
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        return (int)left;
    }
};