#include <vector>
#include <algorithm>

namespace
{
class Solution 
{
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        const auto M = static_cast<int>(grid.size());
        const auto N = static_cast<int>(grid[0].size());
        std::vector<int> prev_row(N, 0);
        std::vector<int> curr_row(N, 0);
        auto p_prev = &prev_row;
        auto p_curr = &curr_row;

        (*p_curr)[0] = grid[0][0];
        for (auto j = 1; j < N; ++j)
        {
            (*p_curr)[j] = grid[0][j] + (*p_curr)[j - 1];
        }

        std::swap(p_curr, p_prev);

        for (auto i = 1; i < M; ++i)
        {
            (*p_curr)[0] = grid[i][0] + (*p_prev)[0];
            for (auto j = 1; j < N; ++j)
            {
                (*p_curr)[j] = std::min(grid[i][j] + (*p_curr)[j - 1], grid[i][j] + (*p_prev)[j]);
            }

            std::swap(p_curr, p_prev);
        }

        return (*p_prev)[N-1];
    }

    int minPathSum_a_lot_of_memory(std::vector<std::vector<int>>& grid) 
    {
        const auto M = static_cast<int>(grid.size());
        const auto N = static_cast<int>(grid[0].size());

        std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));
        for (auto i = 0; i < M; ++i)
        {
            for (auto j = 0; j < N; ++j)
            {
                if (i == 0 && j == 0)
                {
                    dp[i][j] = grid[i][j];
                }
                else if (i == 0)
                {
                    dp[i][j] = grid[i][j] + dp[i][j - 1];
                }
                else if (j == 0)
                {
                    dp[i][j] = grid[i][j] + dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = std::min(grid[i][j] + dp[i - 1][j], grid[i][j] + dp[i][j - 1]);
                }
            }
        }

        return dp[M - 1][N - 1];
    }
};
}

void MinimumPathSum()
{
    Solution sol;
    std::vector<std::vector<int>> grid = { {1, 3, 1},{1, 5, 1},{4, 2, 1} };
    auto res = sol.minPathSum(grid);
}