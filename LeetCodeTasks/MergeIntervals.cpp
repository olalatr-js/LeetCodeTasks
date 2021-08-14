#include <vector>
#include <algorithm>

namespace
{
class Solution
{
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals)
    {
        if (intervals.empty())
            return {};

        std::sort(intervals.begin(), intervals.end(),
            [](const auto& lhs, const auto& rhs) {return lhs[0] < rhs[0]; });

        std::vector<std::vector<int>> res;
        auto beg = intervals[0][0], end = intervals[0][1];
        auto N = static_cast<int>(intervals.size());
        for (auto idx = 1; idx < N; ++idx)
        {
            const auto& next_interval = intervals[idx];
            if (next_interval[0] <= end)
            {
                end = std::max(end, next_interval[1]);
            }
            else // next_interval[0] > end
            {
                res.push_back({ beg, end });
                beg = next_interval[0];
                end = next_interval[1];
            }
        }

        res.push_back({ beg, end });

        return res;
    }
};
}