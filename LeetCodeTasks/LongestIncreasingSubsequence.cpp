#include <vector>
#include <algorithm>
#include <cassert>

namespace
{
class Solution
{
public:
    int lengthOfLIS(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        std::vector<int> LIS(N);
        LIS[0] = 1;
        for (auto i = 1; i < N; ++i)
        {
            LIS[i] = 1;
            for (auto j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                    LIS[i] = std::max(LIS[i], 1 + LIS[j]);
            }
        }

        return *std::max_element(LIS.begin(), LIS.end());
    }
};
}

void LongestIncreasingSubsequence()
{
    Solution sol;
    std::vector<int> nums;
    int res;

    nums = {10, 9, 2, 5, 3, 7, 101, 18};
    res = sol.lengthOfLIS(nums);
    assert(4 == res);

    nums = { 0, 1, 0, 3, 2, 3 };
    res = sol.lengthOfLIS(nums);
    assert(4 == res);

    nums = { 7, 7, 7, 7, 7, 7, 7 };
    res = sol.lengthOfLIS(nums);
    assert(1 == res);

    nums = { 1,3,6,7,9,4,10,5,6 };
    res = sol.lengthOfLIS(nums);
    assert(6 == res);
}