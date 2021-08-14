#include <vector>
#include <algorithm>

namespace
{
class Solution
{
public:
    int minSubArrayLen(int target, std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        auto len = INT_MAX;
        auto sum = 0;
        auto j = 0;
        for (auto i = 0; i < N; ++i)
        {
            while (j < N && sum < target)
            {
                sum += nums[j];
                ++j;
            }

            if (sum >= target)
                len = std::min(len, j - i);

            sum -= nums[i];
        }

        return (len == INT_MAX) ? 0 : len;
    }
private:
    int minSubArrayLen_bin_search(int target, std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        std::vector<int> acc(N + 1);
        acc[0] = 0;
        for (auto i = 1; i <= N; ++i)
        {
            acc[i] = acc[i - 1] + nums[i - 1];
        }

        auto len = INT_MAX;
        for (auto i = 0; i < N; ++i)
        {
            const auto to_search = target + acc[i];
            const auto itr = std::lower_bound(acc.begin() + i, acc.end(), to_search);
            if (itr != acc.end())
            {
                len = std::min(len, static_cast<int>(itr - acc.begin() - i));
            }
        }

        return (len == INT_MAX) ? 0 : len;
    }

    int minSubArrayLen_accepted_but_slow(int target, std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        if (N < 1)
            return 0;

        std::vector<int> acc(N + 1);
        acc[0] = 0;
        for (auto i = 1; i <= N; ++i)
        {
            acc[i] = acc[i - 1] + nums[i - 1];
        }

        auto len = INT_MAX;
        for (auto i = 0; i <= N; ++i)
        {
            for (auto j = i + 1; j <= N; ++j)
            {
                if (acc[j] - acc[i] >= target)
                {
                    len = std::min(len, j - i);
                    break;
                }
            }
        }

        return (len == INT_MAX) ? 0 : len;
    }
};
}

void MinimumSizeSubarraySum()
{

}