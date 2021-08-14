#include <vector>
#include <stack>
#include <unordered_set>
#include <cassert>

namespace
{
class Solution
{
private:
    enum class State
    {
        NotVisited,
        InStack,
        Done
    };

    /*
    void iterativeDFS(int node, const std::vector<std::vector<int>>& graph)
    {
        std::stack<int> stk;
        m_states[node] = State::InStack;
        stk.push(node);
        bool cycle_found = false;
        while (!stk.empty())
        {
            const auto curr = stk.top();
            stk.pop();
            const auto& neibours = graph[curr];
            for (auto n : neibours)
            {
                if (State::InStack == m_states[n])
                {
                    m_connected_to_cycle[n] = true;
                    m_states[n] = State::Done;
                    cycle_found = true;
                    break;
                }

                if (State::Done == m_states[n])
                    continue;

                m_states[n] = State::InStack;
                stk.push(n);
            }

            if (cycle_found)
            {
                // unwind stack
                while (!stk.empty())
                {
                    const auto curr = stk.top();
                    stk.pop();
                    m_states[curr] = State::Done;
                    m_connected_to_cycle[curr] = true;
                }
            }
        }
    }
    */

    bool can_reach_cycle_iterative(int node, const std::vector<std::vector<int>>& graph)
    {
        if (State::InStack == m_states[node])
            return true;

        if (State::Done == m_states[node])
            return false;

        m_states[node] = State::InStack;
        std::stack<int> stk;
        stk.push(node);
        while (!stk.empty())
        {
            const auto curr = stk.top();
            std::stack<int> to_add;
            const auto& neibours = graph[curr];
            for (auto n : neibours)
            {
                if (State::Done == m_states[n])
                    continue;

                if (State::InStack == m_states[n])
                {
                    return true;
                }

                to_add.push(n);
            }

            if (to_add.empty())
            {
                m_states[curr] = State::Done;
                stk.pop();
                continue;
            }

            while (!to_add.empty())
            {
                const auto a = to_add.top();
                to_add.pop();
                m_states[a] = State::InStack;
                stk.push(a);
            }
        }

        return false;
    }

    bool can_reach_cycle(int node, const std::vector<std::vector<int>>& graph)
    {
        if (State::InStack == m_states[node])
            return true;

        if (State::Done == m_states[node])
            return false;

        m_states[node] = State::InStack;
        const auto& neibours = graph[node];
        for (auto n : neibours)
        {
            if (State::InStack == m_states[n] || can_reach_cycle(n, graph))
            {
                return true;
            }
        }

        m_states[node] = State::Done;
        return false;
    }

    int m_N;
    std::vector<State> m_states;
public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
        m_N = static_cast<int>(graph.size());
        m_states = std::vector<State>(m_N, State::NotVisited);
        std::vector<int> res;
        for (auto node = 0; node < m_N; ++node)
        {
            if (!can_reach_cycle_iterative(node, graph))
                res.push_back(node);
        }

        return res;
    }
};
}

void FindEventualSafeStates()
{
    Solution sol;
    std::vector<std::vector<int>> graph = { {1, 2}, {2, 3}, {5}, {0}, {5}, {}, {} };
    auto res = sol.eventualSafeNodes(graph);
    std::vector<int> expected{ 2, 4, 5, 6 };
    assert(res == expected);

    graph = { {1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {} };
    res = sol.eventualSafeNodes(graph);
    expected = { 4 };
    assert(res == expected);
}