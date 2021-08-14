#include <vector>
#include <algorithm>

namespace
{
class Solution 
{
public:
    void nextPermutation(std::vector<int>& nums) 
    {
        const auto N = static_cast<int>(nums.size());
        if (N < 2)
            return;

        auto left = N - 2;
        while (left >= 0 && nums[left] >= nums[left + 1])
            --left;

        if (left >= 0)
        {
            auto right = left + 1;
            while (right + 1 < N && nums[right + 1] > nums[left])
                ++right;

            std::swap(nums[left], nums[right]);
        }

        reverse(nums, left + 1, N - 1);
    }

    static void reverse(std::vector<int>& nums, int left, int right)
    {
        while (left < right)
        {
            std::swap(nums[left++], nums[right--]);
        }
    }
};
}

void NextPermutation()
{
    Solution sol;

    std::vector<int> nums{ 3, 4, 2, 1 };
    sol.nextPermutation(nums); // {4, 1, 2, 3}

    nums = { 8, 9, 9, 9 };
    sol.nextPermutation(nums); // {9, 8, 9, 9}

    nums = { 4, 3, 2, 1 };
    sol.nextPermutation(nums);
}