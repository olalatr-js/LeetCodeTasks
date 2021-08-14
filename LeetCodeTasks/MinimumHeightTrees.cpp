#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace
{
class Solution
{
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> adj_list(n);
        std::vector<int> degrees(n, 0);
        build_adj_list(n, edges, adj_list, degrees);

        std::queue<int> leaves;
        for (auto node = 0; node < n; ++node)
        {
            if (degrees[node] <= 1)
                leaves.push(node);
        }

        auto removed_count = 0;
        while (removed_count < n - 2)
        {
            const auto N = static_cast<int>(leaves.size());
            for (auto i = 0; i < N; ++i)
            {
                const auto curr = leaves.front();
                leaves.pop();

                --degrees[curr];
                if (0 == degrees[curr])
                    ++removed_count;

                const auto& neighbors = adj_list[curr];
                for (auto n : neighbors)
                {
                    --degrees[n];
                    if (1 == degrees[n])
                        leaves.push(n);
                }
            }
        }

        std::vector<int> res;
        while (!leaves.empty())
        {
            res.push_back(leaves.front());
            leaves.pop();
        }

        return res;
    }
private:
    void build_adj_list(int n, const std::vector<std::vector<int>>& edges, 
        std::vector<std::vector<int>>& adj_list, std::vector<int>& degrees)
    {
        for (const auto& e : edges)
        {
            adj_list[e[0]].push_back(e[1]);
            adj_list[e[1]].push_back(e[0]);
            ++degrees[e[0]];
            ++degrees[e[1]];
        }
    }

private:
    std::vector<int> correct_fast_but_consumes_a_lot_of_memory(int n, std::vector<std::vector<int>>& edges)
    {
        auto adj_map = build_adj_map(n, edges);
        std::queue<int> leaves;
        for (const auto& p : adj_map)
        {
            if (p.second.size() == 1u)
                leaves.push(p.first);
        }

        constexpr size_t centroids_num = 2u;
        while (adj_map.size() > centroids_num)
        {
            const auto N = static_cast<int>(leaves.size());
            for (auto i = 0; i < N; ++i)
            {
                const auto leaf = leaves.front();
                leaves.pop();

                //for (auto& p : adj_map)
                //{
                //    p.second.erase(leaf);
                //}

                const auto& leaf_neighbors = adj_map.find(leaf)->second;
                for (const auto& n : leaf_neighbors)
                {
                    auto& neighbor_neighbors = adj_map.find(n)->second;
                    neighbor_neighbors.erase(leaf);
                    if (neighbor_neighbors.size() == 1u)
                    {
                        leaves.push(n);
                    }
                }

                adj_map.erase(leaf);
            }
        }

        std::vector<int> res;
        for (const auto& p : adj_map)
            res.push_back(p.first);

        return res;
    }
private:
    std::unordered_map< int, std::unordered_set<int> > build_adj_map(int n, const std::vector<std::vector<int>>& edges)
    {
        std::unordered_map<  int, std::unordered_set<int> > adj_map(n);
        for (auto i = 0; i < n; ++i)
            adj_map.insert({ i, {} });

        for (const auto e : edges)
        {
            adj_map[e[0]].insert(e[1]);
            adj_map[e[1]].insert(e[0]);
        }

        return adj_map;
    }

private:
    std::vector<int> correct_but_time_exceeded(int n, std::vector<std::vector<int>>& edges)
    {
        const auto adj_list = build_adj_list(n, edges);
        std::vector<int> root2height(n, -1);
        int min_h = INT_MAX;
        for (auto root = 0; root < n; ++root)
        {
            const auto h = find_height(root, adj_list);
            root2height[root] = h;
            if (h < min_h)
                min_h = h;
        }

        std::vector<int> res;
        for (auto root = 0; root < n; ++root)
        {
            if (root2height[root] == min_h)
                res.push_back(root);
        }
        return res;
    }

    int find_height(int root, const std::vector<std::vector<int>>& adj_list)
    {
        auto h = -1;
        std::vector<bool> visited(adj_list.size(), false);
        std::queue<int> q;
        q.push(root);
        while (!q.empty())
        {
            const auto N = static_cast<int>(q.size());
            for (auto i = 0; i < N; ++i)
            {
                auto curr = q.front();
                q.pop();
                if (visited[curr])
                    continue;

                const auto& neighbors = adj_list[curr];
                for (const auto n : neighbors)
                {
                    if (visited[n])
                        continue;

                    q.push(n);
                }

                visited[curr] = true;
            }

            ++h;
        }

        return h;
    }

    std::vector<std::vector<int>> build_adj_list(int n, const std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> adj_list(n);
        for (const auto& e : edges)
        {
            adj_list[e[0]].push_back(e[1]);
            adj_list[e[1]].push_back(e[0]);
        }

        return adj_list;
    }

};
}

void MinimumHeightTrees()
{
    Solution sol;
    auto n = 4;
    std::vector<std::vector<int>> edges{ {1, 0},{1, 2},{1, 3} };
    auto res = sol.findMinHeightTrees(n, edges);
}