#include <algorithm>
#include <vector>

namespace
{
class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        const auto M = static_cast<int>(matrix.size());
        const auto N = static_cast<int>(matrix[0].size());
        auto l = 0;
        auto r = M - 1;
        auto mid = (l + r) / 2;
        while (l != r)
        {
            auto mid = (l + r) / 2;
            if (matrix[mid][N - 1] < target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }

        const auto& row = matrix[r];
        if (target > row[N - 1])
            return false;

        const auto col_itr = std::lower_bound(row.begin(), row.end(), target);
        if (col_itr == row.end())
            return false;
        return *col_itr == target;
    }

private:
    // Runtime : 4 ms, faster than 76.44 % of C++ online submissions for Search a 2D Matrix.
    // Memory Usage : 9.4 MB, less than 77.50 % of C++ online submissions for Search a 2D Matrix.
    bool searchMatrix_lb(std::vector<std::vector<int>>& matrix, int target)
    {
        const auto N = static_cast<int>(matrix[0].size());
        const auto row_itr = std::lower_bound(matrix.begin(), matrix.end(), target,
            [N](const auto& lhs, const auto& rhs) { return lhs[N - 1] < rhs; });
        if (row_itr == matrix.end())
            return false;

        const auto& row = *row_itr;
        const auto col_itr = std::lower_bound(row.begin(), row.end(), target);
        if (col_itr == row.end())
            return false;
        return *col_itr == target;
    }
};
}

void SearchA2DMatrix()
{
    Solution sol;
    std::vector<std::vector<int>> matrix;
    int target;
    bool res;

    matrix = { {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60} };
    target = 3;
    res = sol.searchMatrix(matrix, target);
}