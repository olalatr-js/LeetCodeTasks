#include <vector>
#include <queue>
#include <algorithm>

namespace
{
class Solution
{
public:
    enum class Color
    {
        Undefined,
        Red,
        Blue
    };

    bool isBipartite(std::vector<std::vector<int>>& graph)
    {
        const auto N = static_cast<int>(graph.size());
        std::vector<Color> colors(N, Color::Undefined);
        std::queue<int> q;
        Color curr_col = Color::Red;
        Color next_col = Color::Blue;
        for (auto i = 0; i < N; ++i)
        {
            if (colors[i] != Color::Undefined)
                continue;

            q.push(i);
            colors[i] = curr_col;
            while (!q.empty())
            {
                const auto Nq = static_cast<int>(q.size());
                for (auto j = 0; j < Nq; ++j)
                {
                    const auto curr_node = q.front();
                    q.pop();

                    const auto& neibours = graph[curr_node];
                    for (auto n : neibours)
                    {
                        if (colors[n] == curr_col)
                            return false;
                        else if (colors[n] == Color::Undefined)
                        {
                            q.push(n);
                            colors[n] = next_col;
                        }
                    }
                }

                std::swap(curr_col, next_col);
            }  
        }

        return true;

    }
};
}

void IsGraphBipartite()
{
    Solution sol;
    std::vector<std::vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    auto res = sol.isBipartite(graph);
}