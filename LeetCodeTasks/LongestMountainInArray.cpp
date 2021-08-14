#include <vector>
#include <algorithm>
#include <cassert>

namespace
{
class Solution
{
public:
    int longestMountain(std::vector<int>& arr)
    {
        //return brute_force(arr);
        //return dp(arr);
        return two_pointers(arr);
    }

private:
    int two_pointers(const std::vector<int>& arr)
    {
        const auto N = static_cast<int>(arr.size());
        if (N < 3)
            return 0;

        auto i = 0;
        auto max_len = 0;
        while (i < N)
        {
            auto l = i;
            auto r = i;
            while (r + 1 < N && arr[r] < arr[r + 1])
                ++r;

            if (r == i)
            {
                i = r + 1;
                continue;
            }

            auto peak = r;
            while (r + 1 < N && arr[r] > arr[r + 1])
                ++r;

            if (r > peak)
            {
                max_len = std::max(max_len, r - l + 1);
            }

            i = r;
        }

        return max_len;
    }

    int dp(const std::vector<int>& arr)
    {
        const auto N = static_cast<int>(arr.size());
        if (N < 3)
            return 0;

        std::vector<int> less_from_left(N);
        std::vector<int> less_from_right(N);

        less_from_left[0] = 0;
        for (auto i = 1; i < N; ++i)
        {
            if (arr[i - 1] >= arr[i])
                less_from_left[i] = 0;
            else
                less_from_left[i] = 1 + less_from_left[i - 1];
        }

        less_from_right[N - 1] = 0;
        for (auto j = N - 2; j >= 0; --j)
        {
            if (arr[j] <= arr[j + 1])
                less_from_right[j] = 0;
            else
                less_from_right[j] = 1 + less_from_right[j + 1];
        }

        auto max_len = 0;
        for (auto i = 1; i < N - 1; ++i)
        {
            if (less_from_left[i] && less_from_right[i])
                max_len = std::max(max_len, less_from_left[i] + less_from_right[i] + 1);
        }

        return max_len;
    }

    int brute_force(const std::vector<int>& arr)
    {
        const auto N = static_cast<int>(arr.size());
        if (N < 3)
            return 0;

        auto max_len = 0;
        for (auto i = 1; i < N - 1; ++i)
        {
            auto l = i;
            auto r = i;
            while (l - 1 >= 0 && arr[l - 1] < arr[l])
                --l;

            while (r + 1 <= N - 1 && arr[r] > arr[r + 1])
                ++r;

            if (r != i && l != i)
                max_len = std::max(max_len, r - l + 1);
        }

        return max_len;
    }
};
}

void LongestMountainInArray()
{
    Solution sol;
    std::vector<int> arr;
    int res;

    arr = { 2, 1, 4, 7, 3, 2, 5 };
    res = sol.longestMountain(arr);
    assert(res == 5);

    arr = {875, 884, 239, 731, 723, 685};
    res = sol.longestMountain(arr);
    assert(res == 4);
}