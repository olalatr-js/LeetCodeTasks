#include <vector>
#include <stdexcept>

namespace
{
class Solution 
{
public:
    int uniquePathsIII(std::vector<std::vector<int>>& grid) 
    {
        m_M = static_cast<int>(grid.size());
        m_N = static_cast<int>(grid[0].size());
        m_visited = std::vector<std::vector<bool>>(m_M, std::vector<bool>(m_N, false));
        m_not_obstacles_num = 0;
        //m_path.clear();

        // find start
        auto i_start = -1, j_start = -1;
        for (auto i = 0; i < m_M; ++i)
        {
            for (auto j = 0; j < m_N; ++j)
            {
                if (-1 == grid[i][j])
                    continue;
                
                ++m_not_obstacles_num;

                if (1 == grid[i][j])
                {
                    i_start = i;
                    j_start = j;
                }
            }
        }

        if (i_start == -1 || j_start == -1)
        {
            throw std::invalid_argument("Starting point not found");
        }

        return recursive(grid, i_start, j_start, 1);
    }

private:
    int recursive(const std::vector<std::vector<int>>& grid, int i, int j, int path_len)
    {
        if (grid[i][j] == 2)
        {
            if (path_len == m_not_obstacles_num)
            {
                return 1;
            }

            return 0;
        }

        m_visited[i][j] = true;
        //m_path.push_back({ i, j });

        auto res = 0;
        if (i > 0 && !m_visited[i - 1][j] && (grid[i-1][j] == 0 || grid[i-1][j] == 2))
        {
            res += recursive(grid, i - 1, j, path_len + 1);
        }

        if (j > 0 && !m_visited[i][j - 1] && (grid[i][j - 1] == 0 || grid[i][j - 1] == 2))
        {
            res += recursive(grid, i, j - 1, path_len + 1);
        }

        if (i < m_M - 1 && !m_visited[i + 1][j] && (grid[i + 1][j] == 0 || grid[i + 1][j] == 2))
        {
            res += recursive(grid, i + 1, j, path_len + 1);
        }

        if (j < m_N - 1 && !m_visited[i][j + 1] && (grid[i][j + 1] == 0 || grid[i][j + 1] == 2))
        {
            res += recursive(grid, i, j + 1, path_len + 1);
        }

        //m_path.pop_back();
        m_visited[i][j] = false;
        return res;
    }

    int m_M;
    int m_N;
    int m_not_obstacles_num;
    std::vector<std::vector<bool>> m_visited;
    //std::vector<std::pair<int,int>> m_path;
};
}

void UniquePathsIII()
{
    Solution sol;
    std::vector<std::vector<int>> grid{ {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1} };
    auto res = sol.uniquePathsIII(grid);
}