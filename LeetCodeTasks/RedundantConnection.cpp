#include <vector>
#include <stdexcept>
#include <cassert>

namespace
{
class Solution
{
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges)
    {
        UF uf(edges.size());
        for (const auto& edge : edges)
        {
            if (uf.connected(edge[0], edge[1]))
                return edge;

            uf.unite(edge[0], edge[1]);
        }

        throw std::invalid_argument("Never gets here !!! Unexpected input");
    }

private:
    struct UF
    {
        UF(int N) :parent(N + 1)
        {
            for (auto i = 0; i < N + 1; ++i)
            {
                parent[i] = i;
            }
        }

        int root(int i)
        {
            auto old_i = i;
            while (i != parent[i])
            {
                i = parent[i];
            }

            while (old_i != parent[old_i])
            {
                old_i = parent[old_i];
                parent[old_i] = i;
            }

            return i;
        }

        bool connected(int i, int j)
        {
            return (root(i) == root(j));
        }

        void unite(int i, int j)
        {
            const auto ri = root(i);
            const auto rj = root(j);
            parent[rj] = ri;
        }

    private:
        std::vector<int> parent;
    };
};
}

void RedundantConnection()
{
    Solution sol;
    std::vector<std::vector<int>> edges {{1, 2}, {1, 3}, {2, 3}};
    std::vector<int> expected{2, 3};
    auto res = sol.findRedundantConnection(edges);
    assert(res == expected);

    edges = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    expected = { 1, 4 };
    res = sol.findRedundantConnection(edges);
    assert(res == expected);

    edges = { {3, 4}, {1, 2}, {2, 4}, {3, 5}, {2, 5} };
    expected = {2, 5};
    res = sol.findRedundantConnection(edges);
    assert(res == expected);
}