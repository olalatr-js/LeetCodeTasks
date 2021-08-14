#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>

namespace
{
class Solution
{
public:
    bool canPartitionKSubsets(std::vector<int>& nums, int k)
    {
        const auto total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total == 0 || total % k)
            return false;

        std::sort(nums.begin(), nums.end(), [](int lhs, int rhs) {return lhs > rhs; });
        m_target = total / k;
        m_sums = std::vector<int>(k, 0);
        m_k = k;

        return dfs(nums, 0u);
    }

private:
    bool dfs(const std::vector<int>& nums, size_t pos)
    {
        if (pos == nums.size())
        {
            auto res = true;
            for (auto s : m_sums)
                res = res && (s == m_target);
            return res;
        }

        auto res = false;
        for (auto j = 0; j < m_k; ++j)
        {
            if (m_sums[j] + nums[pos] > m_target)
                continue;

            m_sums[j] += nums[pos];
            res = res || dfs(nums, pos + 1);
            m_sums[j] -= nums[pos]; // backtrack

            if (res)
                break; // solution fuond! There is no sence to continue
        }

        return res;
    }

    std::vector<int> m_sums;
    int m_target;
    int m_k;
};
}

void PartitionToKEqualSumSubsets()
{
    Solution sol;
    std::vector<int> nums;
    int k;
    bool res;

    nums = { 4, 3, 2, 3, 5, 2, 1 };
    k = 4;
    res = sol.canPartitionKSubsets(nums, k);
    assert(res == true);
}