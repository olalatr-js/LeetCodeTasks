#include <vector>
#include <cassert>

namespace
{
class Solution 
{
public:
    int uniquePaths(int m, int n)
    {
        int min_dim, max_dim;
        if (m < n)
        {
            min_dim = m;
            max_dim = n;
        }
        else
        {
            min_dim = n;
            max_dim = m;
        }

        std::vector<unsigned int> curr(min_dim + 1);
        std::vector<unsigned int> next(min_dim + 1, 0u);
        auto p_curr = &curr;
        auto p_next = &next;
        for (auto i = max_dim - 1; i >= 0; --i)
        {
            for (auto j = min_dim - 1; j >= 0; --j)
            {
                if (i == max_dim - 1 && j == min_dim - 1)
                {
                    (*p_curr)[j] = 1;
                }
                else
                {
                    (*p_curr)[j] = (*p_curr)[j + 1] + (*p_next)[j];
                }
            }

            std::swap(p_curr, p_next);
        }

        return (*p_next)[0];

    }

    int uniquePaths_a_lot_of_memory(int m, int n) 
    {
        std::vector< std::vector<unsigned int> > dp(m + 1, std::vector<unsigned int>(n + 1, 0u));   
        for (auto i = m - 1; i >= 0; --i)
        {
            for (auto j = n - 1; j >= 0; --j)
            {
                if (i == m - 1 && j == n - 1)
                {
                    dp[m - 1][n - 1] = 1u;
                }
                else
                {
                    dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
                }
            }
        }

        return dp[0][0];
    }
};
}

void UniquePaths()
{
    Solution sol;
    auto res = sol.uniquePaths(1, 1);
    assert(res == 1);

    res = sol.uniquePaths(3, 7);
    assert(res == 28);

    res = sol.uniquePaths(4, 9);
    assert(res == 165);
}