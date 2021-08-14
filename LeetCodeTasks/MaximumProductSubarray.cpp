#include <vector>
#include <algorithm>
#include <cassert>

namespace
{
class Solution
{
public:
    int maxProduct(std::vector<int>& nums)
    {
        // We need both min and max because multiplication by negative number switches min and max
        int curr_min = nums[0];
        int curr_max = nums[0];
        int res = nums[0];
        for (auto i = 1u; i < nums.size(); ++i)
        {
            auto min_prod = curr_min * nums[i];
            auto max_prod = curr_max * nums[i];
            curr_min = std::min(nums[i], std::min(min_prod, max_prod));
            curr_max = std::max(nums[i], std::max(min_prod, max_prod));
            res = std::max(res, curr_max);
        }

        return res;
    }
private:
    int maxProduct_correct_but_Time_Limit_Exceeded(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        if (N == 1)
            return nums[0];

        int res = INT_MIN;
        std::vector<int> prod(N);
        for (auto start_idx = 0; start_idx < N; ++start_idx)
        {
            prod[start_idx] = nums[start_idx];
            res = std::max(res, prod[start_idx]);
            for (auto end_idx = start_idx + 1; end_idx < N; ++end_idx)
            {
                prod[end_idx] = prod[end_idx - 1] * nums[end_idx];
                res = std::max(res, prod[end_idx]);
            }
        }

        return res;
    }
};
}

void MaximumProductSubarray()
{
    Solution sol;
    std::vector<int> nums;
    int res;

    nums = {2, 3, -2, 4};
    res = sol.maxProduct(nums);
    assert(6 == res);
}