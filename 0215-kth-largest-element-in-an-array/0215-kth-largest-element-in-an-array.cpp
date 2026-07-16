class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        int target = nums.size() - k;

        int left = 0;
        int right = nums.size() - 1;

        while(left <= right)
        {
            int pivot = nums[left + rand() % (right - left + 1)];

            int lt = left;
            int i = left;
            int gt = right;

            while(i <= gt)
            {
                if(nums[i] < pivot)
                {
                    swap(nums[i], nums[lt]);
                    i++;
                    lt++;
                }
                else if(nums[i] > pivot)
                {
                    swap(nums[i], nums[gt]);
                    gt--;
                }
                else
                {
                    i++;
                }
            }

            if(target < lt)
            {
                right = lt - 1;
            }
            else if(target > gt)
            {
                left = gt + 1;
            }
            else
            {
                return nums[target];
            }
        }

        return -1;
    }
};