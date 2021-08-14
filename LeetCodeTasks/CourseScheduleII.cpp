#include <vector>
#include <algorithm>

namespace
{
class Solution
{
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        m_labels.assign(numCourses, label::not_visited);
        build(numCourses, prerequisites);

        m_res.clear();
        for (auto start_node=0; start_node < numCourses; ++start_node)
        {
            if (!dfs(start_node))
                return {};
        }

        std::reverse(m_res.begin(), m_res.end());
        return m_res;
    }

private:
    enum class label
    {
        not_visited,
        processing,
        processed
    };

    bool dfs(int start_node)
    {
        if (label::processed == m_labels[start_node])
            return true;

        m_labels[start_node] = label::processing;
        const auto& adj_nodes = m_adjacency_list[start_node];
        for (const auto adj_n : adj_nodes)
        {
            if (label::processing == m_labels[adj_n])
                return false;
            if (!dfs(adj_n))
                return false;
        }

        m_labels[start_node] = label::processed;
        m_res.push_back(start_node);
        return true;
    }

    void build(int numCourses, const std::vector<std::vector<int>>& prerequisites)
    {
        m_adjacency_list.assign(numCourses, std::vector<int>());
        for (const auto& pr : prerequisites)
        {
            m_adjacency_list[pr[1]].push_back(pr[0]);
        }
    }

    std::vector<std::vector<int>> m_adjacency_list;
    std::vector<label> m_labels;
    std::vector<int> m_res;
};
}

void CourseScheduleII()
{
    Solution sol;
    auto numCourses = 4;
    std::vector<std::vector<int>> prerequisites{ {1, 0}, {2, 0}, {3, 1}, {3, 2} }; // expected {0,2,1,3}
    auto res = sol.findOrder(numCourses, prerequisites);

    numCourses = 8;
    prerequisites = {{1, 0}, {2, 6}, {1, 7}, {5, 1}, {6, 4}, {7, 0}, {0, 5}}; // expected {}
    res = sol.findOrder(numCourses, prerequisites);
}