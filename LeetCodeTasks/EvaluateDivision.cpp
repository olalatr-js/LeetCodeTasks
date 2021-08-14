#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

namespace
{
class Solution
{
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations, std::vector<double>& values,
        std::vector<std::vector<std::string>>& queries)
    {
        std::tie(m_str2idx, m_adj_list) = build(equations, values);
        m_uf = UF(m_adj_list.size());

        std::vector<double> res;
        res.reserve(queries.size());
        for (const auto& q : queries)
        {
            res.push_back(find_path(q[0], q[1]));
        }

        return res;
    }

private:
    struct UF
    {
        UF() = default;
        UF(int N) {}
    };

    struct WeightedVertexTo
    {
        int to;
        double weight;
    };

    static std::tuple< std::unordered_map<std::string, int>, std::unordered_map<int, std::vector<WeightedVertexTo>> >
        build(const std::vector<std::vector<std::string>>& equations, const std::vector<double>& values)
    {
        const auto N = equations.size();
        std::unordered_map<std::string, int> str2idx;
        std::unordered_map<int, std::vector<WeightedVertexTo>> adj_list(N);

        auto count = 0;
        for (size_t i = 0; i < N; ++i)
        {
            const auto& eq = equations[i];
            int idx0, idx1;
            const auto itr0 = str2idx.find(eq[0]);
            if (itr0 == str2idx.end())
            {
                str2idx.insert({eq[0], count});
                idx0 = count;
                ++count;
            }
            else
            {
                idx0 = itr0->second;
            }

            const auto itr1 = str2idx.find(eq[1]);
            if (itr1 == str2idx.end())
            {
                str2idx.insert({ eq[1], count });
                idx1 = count;
                ++count;
            }
            else
            {
                idx1 = itr1->second;
            }

            adj_list[idx0].push_back({ idx1, values[i] });
            adj_list[idx1].push_back({ idx0, 1. / values[i] });
        }

        return { str2idx, adj_list };
    }

    double find_path(const std::string& from, const std::string& to)
    {
        const auto from_itr = m_str2idx.find(from);
        const auto to_itr = m_str2idx.find(to);
        const auto end_itr = m_str2idx.end();
        if (from_itr == end_itr || to_itr == end_itr)
            return -1.;

        const auto from_idx = from_itr->second;
        const auto to_idx = to_itr->second;
        if (from_idx == to_idx)
            return 1.;

        m_visited.clear();
        m_stop = false;
        dfs(from_idx, to_idx, 1.);
        return (m_stop == false)? -1.: m_res;
    }

    void dfs(int from_idx, int to_idx, double prev_val)
    {
        m_visited.insert(from_idx);
        const auto& to_edges = m_adj_list.find(from_idx)->second;
        for (const auto& e : to_edges)
        {
            if (m_visited.end() != m_visited.find(e.to))
                continue;

            if (e.to == to_idx)
            {
                m_res = prev_val * e.weight;
                m_stop = true;
                return;
            }

            dfs(e.to, to_idx, prev_val * e.weight);

            if (m_stop)
                return;
        }

        //throw std::logic_error("Graph has contradictions");
    }

    UF m_uf;
    std::unordered_map<std::string, int> m_str2idx;
    std::unordered_map<int, std::vector<WeightedVertexTo>> m_adj_list;
    std::unordered_set<int> m_visited;
    bool m_stop;
    double m_res;
};

class FirstAttemptSolution 
{
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations, std::vector<double>& values,
        std::vector<std::vector<std::string>>& queries) 
    {
        const auto adj_list = build(equations, values);
        m_uf = UF(adj_list.size());

        std::vector<double> res;
        res.reserve(queries.size());
        for (const auto& q : queries)
        {
            res.push_back( find_path(adj_list, q[0], q[1]) );
        }

        return res;
    }

private:
    struct UF
    {
        UF() = default;
        UF(int N) {}
    };

    struct WeightedVertexTo
    {
        std::string to;
        double weight;
    };

    std::unordered_map<std::string, std::vector<WeightedVertexTo>> build(const std::vector<std::vector<std::string>>& equations, 
        const std::vector<double>& values)
    {
        const auto N = equations.size();
        std::unordered_map<std::string, std::vector<WeightedVertexTo>> res(N);

        for (size_t i = 0; i < N; ++i)
        {
            const auto& eq = equations[i];
            res[eq[0]].push_back({eq[1], values[i]});
            res[eq[1]].push_back({eq[0], 1./values[i]});
        }

        return res;
    }

    double find_path(const std::unordered_map<std::string, std::vector<WeightedVertexTo>>& adj_list, 
        const std::string& from, const std::string& to)
    {
        const auto from_itr = adj_list.find(from);
        const auto to_itr = adj_list.find(to);
        const auto end_itr = adj_list.end();
        if (from_itr == end_itr || to_itr == end_itr)
            return -1.;
        if (from == to)
            return 1.;

        m_visited.clear();
        m_stop = false;
        dfs(adj_list, from, to, 1.);
        return m_res;
    }

    void dfs(const std::unordered_map<std::string, std::vector<WeightedVertexTo>>& adj_list,
        const std::string& from, const std::string& to, double previous_val)
    {
        m_visited.insert(from);
        const auto& to_edges = adj_list.find(from)->second;
        for (const auto& e : to_edges)
        {
            if (m_visited.end() != m_visited.find(e.to))
                continue;

            if (e.to == to)
            {
                m_res = previous_val * e.weight;
                m_stop = true;
                return;
            }

            dfs(adj_list, e.to, to, previous_val * e.weight);

            if (m_stop)
                return;
        }

        //throw std::logic_error("Graph has contradictions");
    }

    UF m_uf;
    std::unordered_set<std::string> m_visited;
    bool m_stop;
    double m_res;
};
}

void EvaluateDivision()
{
    Solution sol;
    std::vector<std::vector<std::string>> equations{ {"a", "b"},{"b", "c"} };
    std::vector<double> values{ 2.0, 3.0 };
    std::vector<std::vector<std::string>> queries{ {"a", "c"},{"b", "a"},{"a", "e"},{"a", "a"},{"x", "x"} };
    // expected [6.0, 0.5, -1.0, 1.0, -1.0 ]
    auto res = sol.calcEquation(equations, values, queries);

    equations = { {"a", "b"},{"c", "d"} };
    values = {1.0, 1.0};
    queries = { {"a", "c"},{"b", "d"},{"b", "a"},{"d", "c"} };
    // expected [-1., -1., 1., 1.]
    res = sol.calcEquation(equations, values, queries);
}