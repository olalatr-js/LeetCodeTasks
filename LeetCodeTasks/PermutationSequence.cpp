#include <vector>
#include <string>
#include <cassert>

namespace
{
class Solution
{
public:
    std::string getPermutation(int n, int k)
    {
        if (n == 1)
            return std::to_string(1);

        std::vector<int> fact(n);
        fact[0] = 0;
        fact[1] = 1;
        for (auto i = 2; i < n; ++i)
        {
            fact[i] = i * fact[i - 1];
        }

        std::vector<int> nums(n);
        for (auto i = 1; i <= n; ++i)
        {
            nums[i - 1] = i;
        }

        // 1 | {2, 3, 4}
        // 2 | {1, 3, 4}
        // 3 | {1, 2, 4}
        // 4 | {1, 2, 3}
        // {...} has (n-1)! permutations

        std::string res;
        --k; // shift to 0 based numeration
        for (auto i = n - 1; i > 0; --i)
        {
            const auto pos = k / fact[i];
            k = k % fact[i];

            res.push_back('0' + nums[pos]);
            nums.erase(nums.begin() + pos);
        }

        res.push_back('0' + nums.front());
        return res;
    }
};
}

void PermutationSequence()
{
    Solution sol;
    int n, k;
    std::string res;

    n = 3; k = 2;
    res = sol.getPermutation(n, k);
    assert(res == "132");

    n = 3; k = 4;
    res = sol.getPermutation(n, k);
    assert(res == "231");

    n = 3; k = 3;
    res = sol.getPermutation(n, k);
    assert(res == "213");

    n = 7; k = 4231;
    res = sol.getPermutation(n, k);
    assert(res == "6723145");

    n = 5; k = 23;
    res = sol.getPermutation(n, k);
    assert(res == "15423");
}