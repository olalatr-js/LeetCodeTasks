#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cassert>

namespace
{
class Solution 
{
public:
    void solve(std::vector<std::vector<char>>& board)
    {
        if (board.empty())
            return;
        m_N_rows = static_cast<int>(board.size());
        m_N_cols = static_cast<int>(board[0].size());
        std::vector<std::vector<bool>> visited(m_N_rows, std::vector<bool>(m_N_cols, false));

        // start dfs from the border
        auto cluster_id = -1;
        for (auto j = 0; j < m_N_cols; ++j)
        {
            if ('X' == board[0][j])
                continue;

            dfs(board, 0, j);
        }

        for (auto i = 1; i < m_N_rows; ++i)
        {
            if ('X' == board[i][m_N_cols - 1])
                continue;

            dfs(board, i, m_N_cols - 1);
        }

        for (auto j = m_N_cols - 2; j >= 0; --j)
        {
            if ('X' == board[m_N_rows - 1][j])
                continue;

            dfs(board, m_N_rows - 1, j);
        }

        for (auto i = m_N_rows - 2; i > 0; --i)
        {
            if ('X' == board[i][0])
                continue;

            dfs(board, i, 0);
        }

        // If square has been visited mark it by 'O'. Mark by 'X' otherwise
        for (auto i = 0; i < m_N_rows; ++i)
        {
            for (auto j = 0; j < m_N_cols; ++j)
            {
                if (V == board[i][j])
                    board[i][j] = O;
                else
                    board[i][j] = X;
            }
        }
    }
private:
    const char O = 'O';
    const char V = 'V';
    const char X = 'X';

    int m_N_rows;
    int m_N_cols;

    void dfs(std::vector<std::vector<char>>& board, int i, int j)
    {
        board[i][j] = V;

        // top
        if ((i > 0) && (O == board[i - 1][j]))
            dfs(board, i - 1, j);

        // right
        if ((j < m_N_cols - 1) && (O == board[i][j + 1]))
            dfs(board, i, j + 1);

        // bottom
        if ((i < m_N_rows - 1) && (O == board[i + 1][j]))
            dfs(board, i + 1, j);

        // left
        if ((j > 0) && (O == board[i][j - 1]))
            dfs(board, i, j - 1);
    }

    // 20 ms, faster than 51.06%. 10.2 MB, less than 69.67% of C++ online submissions
    void solve_uf(std::vector<std::vector<char>>& board)
    {
        if (board.empty())
            return;
        const auto N_rows = static_cast<int>(board.size());
        const auto N_cols = static_cast<int>(board[0].size());
        UF uf(N_rows * N_cols);

        // traverse inside
        auto idx = N_cols + 1;
        for (auto i = 1; i < N_rows - 1; ++i, idx += 2)
        {
            for (auto j = 1; j < N_cols - 1; ++j, ++idx)
            {
                if ('X' == board[i][j])
                    continue;

                // top
                if ('O' == board[i - 1][j])
                    uf.unite(idx, idx - N_cols);
                // right
                if ('O' == board[i][j + 1])
                    uf.unite(idx, idx + 1);
                // bottom
                if ('O' == board[i + 1][j])
                    uf.unite(idx, idx + N_cols);
                // left
                if ('O' == board[i][j - 1])
                    uf.unite(idx, idx - 1);
            }
        }

        // traverse on border
        auto cluster_id = -1;
        for (auto j = 0; j < N_cols; ++j)
        {
            if ('X' == board[0][j])
                continue;

            if (cluster_id < 0)
                cluster_id = uf.root(j);
            else
                uf.unite(cluster_id, j);
        }

        for (auto i = 1; i < N_rows; ++i)
        {
            if ('X' == board[i][N_cols - 1])
                continue;

            if (cluster_id < 0)
                cluster_id = uf.root(i * N_cols + N_cols - 1);
            else
                uf.unite(cluster_id, i * N_cols + N_cols - 1);
        }

        for (auto j = N_cols - 2; j >= 0; --j)
        {
            if ('X' == board[N_rows - 1][j])
                continue;

            if (cluster_id < 0)
                cluster_id = uf.root((N_rows - 1) * N_cols + j);
            else
                uf.unite(cluster_id, (N_rows - 1) * N_cols + j);
        }

        for (auto i = N_rows - 2; i > 0; --i)
        {
            if ('X' == board[i][0])
                continue;

            if (cluster_id < 0)
                cluster_id = uf.root(i * N_cols);
            else
                uf.unite(cluster_id, i * N_cols);
        }

        // produce final result
        if (cluster_id < 0)
        {
            for (auto i = 0; i < N_rows; ++i)
            {
                std::fill(board[i].begin(), board[i].end(), 'X');
            }
            return;
        }

        idx = 0;
        for (auto i = 0; i < N_rows; ++i)
        {
            for (auto j = 0; j < N_cols; ++j, ++idx)
            {
                if ('X' == board[i][j])
                    continue;

                if (cluster_id != uf.root(idx))
                    board[i][j] = 'X';
            }
        }
    }

    void solve_correct_but_slow(std::vector<std::vector<char>>& board)
    {
        if (board.empty())
            return;
        const auto N_rows = static_cast<int>(board.size());
        const auto N_cols = static_cast<int>(board[0].size());
        UF uf(N_rows*N_cols);

        // traverse inside
        auto idx = N_cols + 1;
        for (auto i = 1; i < N_rows - 1; ++i, idx += 2)
        {
            for (auto j = 1; j < N_cols - 1; ++j, ++idx)
            {
                if ('X' == board[i][j])
                    continue;

                // top
                if ('O' == board[i - 1][j])
                    uf.unite(idx, idx - N_cols);
                // right
                if ('O' == board[i][j + 1])
                    uf.unite(idx, idx + 1);
                // bottom
                if ('O' == board[i + 1][j])
                    uf.unite(idx, idx + N_cols);
                // left
                if ('O' == board[i][j - 1])
                    uf.unite(idx, idx - 1);
            }
        }

        // traverse on border
        std::unordered_set<int> border_roots;
        for (auto j = 0; j < N_cols; ++j)
        {
            if ('O' == board[0][j])
            {
                border_roots.insert(uf.root(j));
            }
        }

        for (auto i = 1; i < N_rows; ++i)
        {
            if ('O' == board[i][N_cols - 1])
                border_roots.insert(uf.root(i * N_cols + N_cols - 1));
        }

        for (auto j = N_cols - 2; j >= 0; --j)
        {
            if ('O' == board[N_rows - 1][j])
                border_roots.insert(uf.root((N_rows - 1) * N_cols + j));
        }

        for (auto i = N_rows - 2; i > 0; --i)
        {
            if ('O' == board[i][0])
                border_roots.insert(uf.root(i * N_cols));
        }


        // produce final result
        idx = 0;
        for (auto i = 0; i < N_rows; ++i)
        {
            for (auto j = 0; j < N_cols; ++j, ++idx)
            {
                if ('X' == board[i][j])
                    continue;

                if (border_roots.end() == border_roots.find(uf.root(idx)))
                    board[i][j] = 'X';
            }
        }
    }
private:
    struct UF
    {
        UF(int N): parent(N)
        {
            for (auto i = 0; i < N; ++i)
                parent[i] = i;
        }

        int root(int i)
        {
            if (parent[i] == i)
                return i;

            auto old_i = i;
            while (i != parent[i])
            {
                i = parent[i]; // parent[parent[i]] = gradparent
            }

            while (old_i != parent[old_i])
            {
                old_i = parent[old_i];
                parent[old_i] = i;
            }

            return i;
        }

        void unite(int i, int j)
        {
            const auto ri = root(i);
            const auto rj = root(j);

            parent[rj] = ri;
        }

        std::vector<int> parent;
    };
};
}

void SurroundedRegions()
{
    Solution sol;
    std::vector<std::vector<char>> board{ {'X', 'X', 'X', 'X'},
                                          {'X', 'O', 'O', 'X'},
                                          {'X', 'X', 'O', 'X'},
                                          {'X', 'O', 'X', 'X'} };
    std::vector<std::vector<char>> expected{ {'X', 'X', 'X', 'X'},
                                             {'X', 'X', 'X', 'X'},
                                             {'X', 'X', 'X', 'X'},
                                             {'X', 'O', 'X', 'X'} };
    sol.solve(board);
    assert(board == expected);

    board = {{'X', 'O', 'X', 'O', 'X', 'O', 'O', 'O', 'X', 'O'}, 
             {'X', 'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'X'},
             {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X'},
             {'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'X'},
             {'O', 'O', 'X', 'X', 'O', 'X', 'X', 'O', 'O', 'O'},
             {'X', 'O', 'O', 'X', 'X', 'X', 'O', 'X', 'X', 'O'},
             {'X', 'O', 'X', 'O', 'O', 'X', 'X', 'O', 'X', 'O'},
             {'X', 'X', 'O', 'X', 'X', 'O', 'X', 'O', 'O', 'X'}, 
             {'O', 'O', 'O', 'O', 'X', 'O', 'X', 'O', 'X', 'O'},
             {'X', 'X', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'O'}};
    expected = {
             {'X', 'O', 'X', 'O', 'X', 'O', 'O', 'O', 'X', 'O'},
             {'X', 'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'X'},
             {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X'},
             {'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'X'},
             {'O', 'O', 'X', 'X', 'O', 'X', 'X', 'O', 'O', 'O'},
             {'X', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'O'},
             {'X', 'O', 'X', 'X', 'X', 'X', 'X', 'O', 'X', 'O'},
             {'X', 'X', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'X'},
             {'O', 'O', 'O', 'O', 'X', 'X', 'X', 'O', 'X', 'O'},
             {'X', 'X', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'O'}};
    sol.solve(board);
    assert(board == expected);

    board = {{'X', 'O', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'X', 'O', 'X'}, {'X', 'O', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'X', 'O', 'X'}};
    expected = {{'X', 'O', 'X', 'O', 'X', 'O'}, {'O', 'X', 'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X', 'X', 'O'}, {'O', 'X', 'O', 'X', 'O', 'X'}};
    sol.solve(board);
    assert(board == expected);
}