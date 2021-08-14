#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>

namespace
{
class Solution
{
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets)
    {
        m_res.clear();
        build(tickets);
        sort_to(m_adj_list);

        dfs("JFK");

        std::reverse(m_res.begin(), m_res.end());
        return m_res;
    }

private:
    struct Edge
    {
        bool operator == (const Edge& other) const
        {
            return (from == other.from) && (to == other.to);
        }

        std::string from;
        std::string to;
    };

    static std::hash<std::string> str_hasher;

    struct EdgeHasher
    {
        size_t operator()(const Edge& e) const
        {
            size_t res = 17;
            res += 31 * res + get_hash(e.from);
            res += 31 * res + get_hash(e.to);
            return res;
        }

    private:
        size_t get_hash(const std::string& s) const
        {
            const auto itr = m_cached.find(s);
            if (m_cached.end() != itr)
            {
                return itr->second;
            }

            const auto c = Solution::str_hasher(s);
            m_cached.insert({s, c});
            return c;
        }

        mutable std::unordered_map<std::string, size_t> m_cached;
    };

    void build(const std::vector<std::vector<std::string>>& tickets)
    {
        m_adj_list.clear();
        m_edge_degrees.clear();
        for (const auto& e : tickets)
        {
            m_adj_list[e[0]].push_back(e[1]);
            ++m_edge_degrees[Edge{ e[0], e[1] }];
        }
    }

    void sort_to(std::unordered_map<std::string, std::vector<std::string>>& adj_list)
    {
        for (auto& p : adj_list)
        {
            auto& to_vect = p.second;
            std::sort(to_vect.begin(), to_vect.end());
        }
    }

    void dfs(const std::string& from)
    {
        const auto adj_itr = m_adj_list.find(from);
        if (adj_itr == m_adj_list.end())
        {
            m_res.push_back(from);
            return;
        }

        const auto& edges_to = adj_itr->second;
        for (const auto& to : edges_to)
        {
            const auto degree_itr = m_edge_degrees.find(Edge{from, to});
            if (degree_itr->second == 0)
                continue;

            --(degree_itr->second);
            dfs(to);
        }

        m_res.push_back(from);
    }

    std::unordered_map<std::string, std::vector<std::string>> m_adj_list;
    std::unordered_map<Edge, int, EdgeHasher> m_edge_degrees;
    std::vector<std::string> m_res;
};

std::hash<std::string> Solution::str_hasher;
}

void ReconstructItinerary()
{
    Solution sol;
    std::vector<std::vector<std::string>> tickets{ {"MUC", "LHR"},{"JFK", "MUC"},{"SFO", "SJC"},{"LHR", "SFO"} };
    auto res = sol.findItinerary(tickets);
    assert((res == std::vector<std::string>{"JFK", "MUC", "LHR", "SFO", "SJC"}));

    tickets = { {"JFK", "SFO"},{"JFK", "ATL"},{"SFO", "ATL"},{"ATL", "JFK"},{"ATL", "SFO"} };
    res = sol.findItinerary(tickets);
    assert((res == std::vector<std::string>{"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"}));

    tickets = {{"EZE", "AXA"}, {"TIA", "ANU"}, {"ANU", "JFK"}, {"JFK", "ANU"}, {"ANU", "EZE"}, {"TIA", "ANU"}, {"AXA", "TIA"}, {"TIA", "JFK"}, {"ANU", "TIA"}, {"JFK", "TIA"}};
    res = sol.findItinerary(tickets);
    assert((res == std::vector<std::string>{"JFK", "ANU", "EZE", "AXA", "TIA", "ANU", "JFK", "TIA", "ANU", "TIA", "JFK"}));

}