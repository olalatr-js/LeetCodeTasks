#include <vector>
#include <stack>
#include <set>
#include <tuple>

namespace
{
class Solution
{
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        auto adjacency_list = edges_list_2_adjacency_list(numCourses, prerequisites);
        m_labels = std::vector<label>(numCourses, label::not_visited);
        std::set<int> starting_nodes;
        for (auto i = 0; i < numCourses; ++i)
            starting_nodes.insert(i);

        while (!starting_nodes.empty())
        {
            const auto start_node = *starting_nodes.cbegin();
            std::stack<  std::tuple<int, int> > stk; // {current node idx, adjacency nodes iteration position}
            m_labels[start_node] = label::processing;
            stk.push({ start_node, 0 });
            while (!stk.empty())
            {
                auto go_into_recursion = false;
                const auto curr_node = std::get<0>(stk.top());
                const auto last_position = std::get<1>(stk.top());
                const auto N = static_cast<int>(adjacency_list[curr_node].size());
                for (auto j = last_position; j < N; ++j)  //const auto adj_node : adjacency_list[curr_node])
                {
                    const auto adj_node = adjacency_list[curr_node][j];
                    if (label::processing == m_labels[adj_node])
                        return false;
                    if (label::not_visited == m_labels[adj_node])
                    {
                        m_labels[adj_node]= label::processing;
                        std::get<1>(stk.top()) = j + 1;
                        stk.push({ adj_node, 0 });
                        go_into_recursion = true;
                        break;
                    }
                }

                if (go_into_recursion)
                    continue;

                m_labels[curr_node] = label::processed;
                stk.pop();
                starting_nodes.erase(curr_node);
            }
        }

        return true;
    }

    bool beats21_88_percent(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        auto adjacency_list = edges_list_2_adjacency_list(numCourses, prerequisites);
        m_labels = std::vector<label>(numCourses, label::not_visited);
        std::set<int> starting_nodes;
        for (auto i = 0; i < numCourses; ++i)
            starting_nodes.insert(i);

        while (!starting_nodes.empty())
        {
            const auto start_node = *starting_nodes.cbegin();
            std::stack<int> stk;
            m_labels[start_node] = label::processing;
            stk.push(start_node);
            while (!stk.empty())
            {
                auto go_into_recursion = false;
                const auto curr_node = stk.top();
                for (const auto adj_node : adjacency_list[curr_node])
                {
                    if (label::processing == m_labels[adj_node])
                        return false;
                    if (label::not_visited == m_labels[adj_node])
                    {
                        m_labels[adj_node] = label::processing;
                        stk.push(adj_node);
                        go_into_recursion = true;
                        break;
                    }
                }

                if (go_into_recursion)
                    continue;

                m_labels[curr_node] = label::processed;
                stk.pop();
                starting_nodes.erase(curr_node);
            }
        }

        return true;
    }

private:
    std::vector<std::vector<int>> edges_list_2_adjacency_list(int numCourses,
        const std::vector<std::vector<int>>& prerequisites)
    {
        std::vector<std::vector<int>> res(numCourses);
        for (const auto& edge : prerequisites)
        {
            res[edge[1]].push_back(edge[0]);
        }

        return res;
    }

    enum class label
    {
        not_visited,
        processing,
        processed
    };

    std::vector<label> m_labels;
};
}

void CourseSchedule()
{
    Solution sol;
    auto numCourses = 4;
    std::vector<std::vector<int>> prerequisites{ {0, 1}, {3, 1}, {1, 3}, {3, 2} }; // expected false
    auto res = sol.canFinish(numCourses, prerequisites);
}