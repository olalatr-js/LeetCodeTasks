#include <vector>
#include <algorithm>

namespace
{
class Solution
{
public:
    std::vector<std::vector<int>> initial_solution_insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
    {
        std::vector<std::vector<int>> res;
        const auto N = static_cast<int>(intervals.size());
        auto i = 0;
        while (i < N && intervals[i][1] < newInterval[0])
        {
            res.push_back(intervals[i]);
            ++i;
        }

        if (i == N)
        {
            res.push_back(newInterval);
            return res;
        }

        auto beg = std::min(intervals[i][0], newInterval[0]);
        int end = newInterval[1];
        while (i < N)
        {
            if (intervals[i][0] > end)
            {
                break;
            }

            if (intervals[i][1] >= end)
            {
                end = intervals[i][1];
                ++i;
                break;
            }

            ++i;
        }

        res.push_back({ beg, end });

        res.insert(res.cend(), intervals.cbegin() + i, intervals.cend());

        return res;
    }

    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
    {
        std::vector<std::vector<int>> res;
        const auto N = static_cast<int>(intervals.size());
        auto i = 0;
        while (i < N && intervals[i][1] < newInterval[0])
        {
            res.push_back(intervals[i]);
            ++i;
        }

        if (i == N)
        {
            res.push_back(newInterval);
            return res;
        }

        auto beg = std::min(intervals[i][0], newInterval[0]);
        auto end = newInterval[1];
        while (i < N && intervals[i][0] <= newInterval[1])
        {
            end = std::max(newInterval[1], intervals[i][1]);
            ++i;
        }

        res.push_back({ beg, end });

        res.insert(res.cend(), intervals.cbegin() + i, intervals.cend());

        return res;
    }
};
}

void InsertInterval()
{
    Solution sol;
    std::vector<std::vector<int>> intervals = { {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16} };
    std::vector<int> newInterval = { 4, 8 };
    auto res = sol.insert(intervals, newInterval);
}