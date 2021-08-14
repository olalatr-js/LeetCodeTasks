#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>

namespace
{
class Solution
{
public:
    int majorityElement(std::vector<int>& nums)
    {
        return majorityElement_shuffle_and_nth_element(nums);
    }

private:
    int majorityElement_shuffle_and_nth_element(std::vector<int>& nums)
    {
        // shuffle
        const auto N = static_cast<int>(nums.size());
        static const auto seed = time(nullptr);
        srand(seed);
        for (auto i = 0; i < N; ++i)
        {
            // r_idx should be in [i; N - 1]
            auto r_idx = rand();
            r_idx = r_idx % (N - i) + i;
            std::swap(nums[i], nums[r_idx]);
        }

        return majorityElement_like_in_Sedgewick(nums);
    }

    // Accepted
    int majorityElement_Moore_counting(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        if (N <= 2)
            return nums[0];

        auto maj_idx = 0;
        auto cnt = 1;
        for (auto i = 1; i < N; ++i)
        {
            if (nums[i] == nums[maj_idx])
                ++cnt;
            else
                --cnt;

            if (cnt == 0)
            {
                maj_idx = i;
                cnt = 1;
            }
        }

        return nums[maj_idx];
    }

    // gives TLE for most sorted array with a lot of duplicate
    int majorityElement_like_in_Sedgewick(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        auto lo = 0;
        auto hi = N - 1;
        const auto k = N / 2;
        auto a = nums.data();
        while (lo < hi)
        {
            const auto p_idx = partition(a, lo, hi);
            if (p_idx == k)
                return nums[k];

            if (p_idx < k) // [lo, p_idx, k, hi]
            {
                lo = p_idx + 1;
            }
            else // p_idx > k; [lo, k, p_idx, hi]
            {
                hi = p_idx - 1;
            }
        }

        return nums[k];
    }

    int majorityElement_TLE(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        my_nth(nums.data(), 0, N / 2, N - 1);
        return nums[N / 2];
    }

    int my_nth(int* a, int lo, int nth, int hi)
    {
        auto p_idx = partition(a, lo, hi);
        if (p_idx < nth) // [lo, p_idx, nth, hi]
        {
            return my_nth(a, p_idx + 1, nth, hi);
        }
        else if (p_idx > nth) // [lo, nth, p_idx, hi]
        {
            p_idx = my_nth(a, lo, nth, p_idx - 1);
        }

        return p_idx;
    }

    int partition(int* a, int lo, int hi)
    {
        if (lo >= hi)
            return lo;

        // pivot element a[lo]
        int j = lo;
        for (auto i = lo + 1; i <= hi; ++i)
        {
            if (a[i] < a[lo])
            {
                ++j;
                std::swap(a[i], a[j]);
            }
        }

        std::swap(a[lo], a[j]);
        return j;
    }

    // Works fine
    int majorityElement_using_stl(std::vector<int>& nums)
    {
        std::nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];
    }
};
}

void MajorityElement()
{
    Solution sol;
    std::vector<int> nums;
    int res;

    nums = {-1, 1, 1, 1, 2, 1};
    res = sol.majorityElement(nums);
    assert(res == 1);

    nums = { 4, 5, 4};
    res = sol.majorityElement(nums);
    assert(res == 4);

    nums = { 4, 5, 4, 4, 1, 2, 3, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4 };
    res = sol.majorityElement(nums);
    assert(res == 4);
}