#include <vector>
#include <cassert>
#include <algorithm>

namespace
{
class Solution 
{
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) 
    {
        const auto N = static_cast<int>(nums.size());
        if (N == 0)
            return { -1, -1 };

        // find low bound
        auto left = 0;
        auto right = N - 1;

        if (target < nums[left] || nums[right] < target)
            return { -1,-1 };

        while (left < right)
        {
            const auto mid = (left + right) / 2;
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else 
            {
                right = mid;
            }
        }

        auto lower = left;
        if (nums[lower] != target)
        {
            return { -1, -1 };
        }

        left = 0;
        right = N - 1;

        while (left < right)
        {
            const auto mid = (left + right) / 2;
            if (!(target < nums[mid]))
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        int upper;
        if (left == N - 1 && nums[left] == target)
        {
            upper = left;
        }
        else
        {
            upper = std::max(0, left - 1);
        }

        return {lower, upper};
    }
};

void test_std_bounds(const std::vector<int>& nums, int target)
{
    auto l_b = std::lower_bound(nums.cbegin(), nums.cend(), target);
    auto u_b = std::upper_bound(nums.cbegin(), nums.cend(), target);
    auto kkk = 1;
}
}

void FindFirsAndLastPositionOfElementInSortedArray()
{
    Solution sol;

    std::vector<int> nums{ 5, 7, 7, 8, 8, 10 };
    auto target = 8;
    auto res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 3);
    assert(res[1] == 4);
    test_std_bounds(nums, target);

    nums = { 1 };
    target = 0;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == -1);
    assert(res[1] == -1);
    test_std_bounds(nums, target);

    nums = { 1 };
    target = 1;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 0);
    assert(res[1] == 0);
    test_std_bounds(nums, target);

    nums = { 5, 7, 7, 8, 8, 10 };
    target = 6;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == -1);
    assert(res[1] == -1);
    test_std_bounds(nums, target);

    nums = { 5, 7, 7, 8, 8, 8, 8, 8, 9, 10 };
    target = 8;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 3);
    assert(res[1] == 7);
    test_std_bounds(nums, target);

    nums = { 8, 8, 8, 9 };
    target = 9;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 3);
    assert(res[1] == 3);
    test_std_bounds(nums, target);

    nums = { 8, 8, 8, 9, 9, 9, 9, 9, 9, 9 };
    target = 9;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 3);
    assert(res[1] == 9);
    test_std_bounds(nums, target);

    nums = { 7, 8, 8, 8};
    target = 7;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 0);
    assert(res[1] == 0);
    test_std_bounds(nums, target);

    nums = { 7, 7, 7, 7, 7, 8, 8, 8 };
    target = 7;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 0);
    assert(res[1] == 4);
    test_std_bounds(nums, target);

    nums = { 8, 8, 8, 9 };
    target = 7;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == -1);
    assert(res[1] == -1);
    test_std_bounds(nums, target);

    nums = { 7, 7, 7, 7, 8, 8, 8 };
    target = 8;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 4);
    assert(res[1] == 6);
    test_std_bounds(nums, target);

    nums = { 7, 7, 7, 7, 8, 8, 8, 9 };
    target = 8;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 4);
    assert(res[1] == 6);
    test_std_bounds(nums, target);

    nums = { 8, 8, 8, 8 };
    target = 8;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 0);
    assert(res[1] == 3);
    test_std_bounds(nums, target);

    nums = { 7, 8, 8, 8 };
    target = 8;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 1);
    assert(res[1] == 3);
    test_std_bounds(nums, target);

    nums = { 8, 8, 8, 9 };
    target = 8;
    res = sol.searchRange(nums, target);
    assert(res.size() == 2);
    assert(res[0] == 0);
    assert(res[1] == 2);
    test_std_bounds(nums, target);
}