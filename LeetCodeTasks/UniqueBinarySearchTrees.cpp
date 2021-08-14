#include <vector>

namespace
{
class Solution 
{
public:
    int numTrees(int n)
    {
        if (n <= 1)
            return 1;

        std::vector<int> dp(n+1);
        dp[0] = 1;
        dp[1] = 1;
        for (auto k = 2; k <= n; ++k)
        {
            dp[k] = 0;
            for (auto i = 1; i <= k; ++i)
            {
                dp[k] += dp[i - 1] * dp[k - i];
            }
        }

        return dp[n];
    }

private:
    int numTrees_correct_but_Time_Limit_Exceeded(int n)
    {
        return recursive(1, n);
    }

    int recursive(int low, int hi)
    {
        if (low >= hi)
            return 1;

        auto res = 0;
        for (auto i = low; i <= hi; ++i)
        {
            auto l_num = recursive(low, i - 1);
            auto r_num = recursive(i + 1, hi);
            res += l_num * r_num;
        }

        return res;
    }
};
}

void UniqueBinarySearchTrees()
{

}