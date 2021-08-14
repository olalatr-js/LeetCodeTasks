#include <vector>
#include <queue>

namespace
{
class Solution
{
public:
    bool possibleBipartition_BFS(int N, std::vector<std::vector<int>>& dislikes)
    {
        const auto adj_list = build(N + 1, dislikes);
        std::vector<Color> colors(N + 1, Color::Undefined);
        for (auto node = 1; node < N + 1; ++node)
        {
            if (colors[node] != Color::Undefined)
                continue;

            std::queue<int> q;
            q.push(node);
            Color curr_col = Color::Red;
            Color next_col = Color::Blue;
            colors[node] = curr_col;
            while (!q.empty())
            {
                const auto n_in_q = static_cast<int>(q.size());
                for (auto i = 0; i < n_in_q; ++i)
                {
                    const auto curr = q.front();
                    q.pop();
                    const auto& neibours = adj_list[curr];
                    for (auto n : neibours)
                    {
                        if (colors[n] == curr_col)
                            return false;
                        if (colors[n] == next_col)
                            continue;

                        colors[n] = next_col;
                        q.push(n);
                    }
                }

                std::swap(curr_col, next_col);
            }
        }

        return true;
    }

    bool possibleBipartition(int N, std::vector<std::vector<int>>& dislikes)
    {
        const auto adj_list = build(N + 1, dislikes);
        std::vector<Color> colors(N + 1, Color::Undefined);
        for (auto node = 1; node < N + 1; ++node)
        {
            if (colors[node] != Color::Undefined)
                continue;

            const auto curr_col = Color::Red;
            colors[node] = curr_col;
            if (!dfs(adj_list, node, colors, curr_col))
                return false;
        }

        return true;
    }

private:
    enum class Color
    {
        Undefined,
        Red,
        Blue
    };

    bool dfs(const std::vector<std::vector<int>>& adj_list, int node, std::vector<Color>& colors, Color curr_col)
    {
        const auto& neibours = adj_list[node];
        Color next_col = curr_col == Color::Red ? Color::Blue : Color::Red;
        for (auto n : neibours)
        {
            if (colors[n] == next_col)
                continue;

            if (colors[n] == curr_col || !dfs(adj_list, n, colors, colors[n] = next_col))
                return false;

            //colors[n] = next_col;
            //if (!dfs(adj_list, n, colors, next_col))
            //    return false;             
        }

        return true;
    }

    std::vector<std::vector<int>> build(int N, const std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> adj_list(N, std::vector<int>());
        for (const auto& e : edges)
        {
            adj_list[e[0]].push_back(e[1]);
            adj_list[e[1]].push_back(e[0]);
        }

        return adj_list;
    }
};
}

void PossibleBipartition()
{
    Solution sol;
    int N = 4;
    std::vector<std::vector<int>> dislikes = {{1, 2}, {1, 3}, {2, 4}};
    auto res = sol.possibleBipartition(N, dislikes);
}