#include <vector>

namespace
{
class Solution
{
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        std::vector<std::vector<int>> res(n, std::vector<int>(n));
        auto i = 0;
        auto n_sq = n * n;
        int row, col;
        auto col_l = 0;
        auto row_t = 0;
        auto col_r = n - 1;
        auto row_b = n - 1;
        while (i < n_sq)
        {
            // left to right
            for (row = row_t, col = col_l; (i < n_sq) && (col <= col_r); ++col, ++i)
            {
                res[row][col] = i + 1;
            }
            ++row_t;

            // top to bottom
            for (row = row_t, col = col_r; (i < n_sq) && (row <= row_b); ++row, ++i)
            {
                res[row][col] = i + 1;
            }
            --col_r;

            // right to left
            for (row = row_b, col = col_r; (i < n_sq) && (col_l <= col); --col, ++i)
            {
                res[row][col] = i + 1;
            }
            --row_b;

            // bottom to top
            for (row = row_b, col = col_l; (i < n_sq) && (row_t <= row); --row, ++i)
            {
                res[row][col] = i + 1;
            }
            ++col_l;
        }

        return res;
    }
};
}

void SpiralMatrixII()
{
    Solution sol;
    int n;
    std::vector<std::vector<int>> res;

    n = 3;
    res = sol.generateMatrix(n);
}