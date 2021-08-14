#include <vector>
#include <numeric>

namespace
{
// Runtime: 200 ms, faster than 39.65 % of C++ online submissions for Partition Equal Subset Sum.
// Memory Usage : 9.4 MB, less than 82.15 % of C++ online submissions for Partition Equal Subset
class Solution
{
public:
    bool canPartition(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        if (N <= 1)
            return false;
        const auto total = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (total % 2)
            return false;

        const auto half = total / 2;

        //std::vector<bool> prev(half + 1, false);
        //std::vector<bool> curr(half + 1, false);
        //prev[0] = true;

        std::vector<unsigned char> prev(half + 1, 0);
        std::vector<unsigned char> curr(half + 1, 0);
        prev[0] = 1;
        for (auto i = 0; i < N; ++i)
        {
            for (auto sum = 1; sum <= half; ++sum)
            {
                // dp[i][sum] = dp[i-1][sum] || dp[i-1][sum - nums[i]]
                curr[sum] = prev[sum];
                if (sum - nums[i] >= 0)
                    curr[sum] = curr[sum] || prev[sum - nums[i]];
            }

            std::swap(curr, prev);
        }

        return prev[half];
    }
};

// Runtime: 436 ms, faster than 9.88 % of C++ online submissions for Partition Equal Subset Sum.
// Memory Usage : 9.2 MB, less than 83.85 % of C++ online submissions for Partition Equal Subset
class Solution_slow 
{
public:
    bool canPartition(std::vector<int>& nums) 
    {
        const auto N = static_cast<int>(nums.size());
        if (N <= 1)
            return false;
        const auto total = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (total % 2)
            return false;

        const auto half = total / 2;
        std::vector<bool> row1(half + 1, false);
        std::vector<bool> row2(half + 1, false);
        std::vector<bool>* prev = &row1;
        std::vector<bool>* curr = &row2;
        (*prev)[0] = true;
        for (auto i = 0; i < N; ++i)
        {
            for (auto sum = 1; sum <= half; ++sum)
            {
                // dp[i][sum] = dp[i-1][sum] || dp[i-1][sum - nums[i]]
                (*curr)[sum] = (*prev)[sum];
                if (sum - nums[i] >= 0)
                    (*curr)[sum] = (*curr)[sum] || (*prev)[sum - nums[i]];
            }

            std::swap(curr, prev);
        }

        return (*prev)[half];
    }
};
}

void PartitionEqualSubsetSum()
{

}