#include "IndexedPriorityQueue.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>

namespace
{
class Solution 
{
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k)
    {
        const auto adj_list = build(times, n);
        std::vector<int> dist_to(n + 1, INT_MAX);
        dist_to[k] = 0;

        IndexedPriorityQueue<int, std::greater<int>> pq(n + 1, std::greater<int>());

        pq.push(k, 0);
        while (!pq.empty())
        {
            const auto curr = pq.top_index();
            pq.pop();
            const auto& neighbours = adj_list[curr];
            for (const auto n : neighbours)
            {
                // relax edge
                if (dist_to[curr] + n.weight < dist_to[n.to])
                {
                    dist_to[n.to] = dist_to[curr] + n.weight;

                    if (pq.contains(n.to))
                        pq.change_key(n.to, dist_to[n.to]);
                    else
                        pq.push(n.to, dist_to[n.to]);
                }
            }
        }

        const auto m = *std::max_element(dist_to.begin() + 1, dist_to.end());
        if (m < INT_MAX)
            return m;

        return -1;
    }

private:
    struct WeightedEdge
    {
        int to;
        int weight;
    };

    std::vector<std::vector<WeightedEdge>> build(std::vector<std::vector<int>>& edges, int n)
    {
        std::vector<std::vector<WeightedEdge>> res(n + 1);
        for (const auto& e : edges)
        {
            res[e[0]].push_back({e[1], e[2]});
        }

        return res;
    }
};
}

void NetworkDelayTime()
{
    Solution sol;
    std::vector<std::vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    auto n = 4;
    auto k = 2;
    auto res = sol.networkDelayTime(times, n, k);
    assert(res == 2);

    times = { {1, 2, 1} };
    n = 2;
    k = 1;
    res = sol.networkDelayTime(times, n, k);
    assert(res == 1);

    times = { {1, 2, 1} }; 
    n = 2;
    k = 2;
    res = sol.networkDelayTime(times, n, k);
    assert(res == -1);

    times = { {1,2,1}, {1,3,2}, {1,4,7}, {1,5,1}, {2,4,3}, {3,4,4}, {5,4,1} };
    n = 5;
    k = 1;
    res = sol.networkDelayTime(times, n, k);
    assert(res == 2);

    times = { {1,2,1}, {1,3,2}, {1,4,7}, {1,5,1}, {2,4,3}, {3,4,4}, {5,4,1}, {4,6,1}, {5,6,2} };
    n = 6;
    k = 1;
    res = sol.networkDelayTime(times, n, k);
    assert(res == 3);

    times = {{4, 2, 76}, {1, 3, 79}, {3, 1, 81}, {4, 3, 30}, {2, 1, 47}, {1, 5, 61}, {1, 4, 99}, {3, 4, 68}, {3, 5, 46}, {4, 1, 6}, {5, 4, 7}, {5, 3, 44}, {4, 5, 19}, {2, 3, 13}, {3, 2, 18}, {1, 2, 0}, {5, 1, 25}, {2, 5, 58}, {2, 4, 77}, {5, 2, 74}};
    n = 5;
    k = 3;
    res = sol.networkDelayTime(times, n, k);
    assert(res == 59);
}