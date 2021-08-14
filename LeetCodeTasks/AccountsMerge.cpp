#include <vector>
#include <string>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <cassert>

namespace
{
class Solution 
{
public:
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>>& accounts)
    {
        if (accounts.size() <= 1)
            return accounts;

        std::unordered_map<std::string, int> email2id;
        auto next_available_id = 0;
        UF uf;
        for (const auto& ac : accounts)
        {
            if (ac.size() < 2)
                continue;

            const auto& first_email = ac[1];
            const auto itr = email2id.find(first_email);
            int curr_id;
            if (itr == email2id.end())
            {
                email2id.insert({first_email, next_available_id});
                curr_id = next_available_id;
                uf.add(next_available_id);
                ++next_available_id;
            }
            else
            {
                curr_id = itr->second;
            }

            for (auto itr_emails = ac.begin() + 2; itr_emails != ac.end(); ++itr_emails)
            {
                const auto itr_id = email2id.find(*itr_emails);
                if (itr_id == email2id.end())
                {
                    email2id.insert({*itr_emails, curr_id});
                }
                else
                {
                    uf.unite(curr_id, itr_id->second);
                }
            }
        }

        // form components
        std::unordered_map<int, std::vector<std::string>> root2component;
        for (const auto& e2i : email2id)
        {
            const auto r = uf.root(e2i.second);
            if (root2component.find(r) == root2component.end())
                root2component.insert({ r, {""} });
            root2component[r].push_back(e2i.first);
        }

        // add names
        for (const auto& ac : accounts)
        {
            if (ac.size() < 2)
                continue;

            const auto& email = ac[1];
            const auto r = uf.root( email2id[email] );
            auto& component = root2component.find(r)->second;
            if (component[0].empty())
                component[0] = ac[0];
        }

        // form output
        std::vector<std::vector<std::string>> res;
        res.reserve(root2component.size());
        for (auto& r2c : root2component)
        {
            std::sort(r2c.second.begin() + 1, r2c.second.end());
            res.push_back(std::move(r2c.second));
        }

        return res;
    }

private:
    struct UF
    {
        void add(int i)
        {
            parent.push_back(i);
        }

        void unite(int i, int j)
        {
            const auto ri = root(i);
            const auto rj = root(j);
            parent[rj] = ri;
        }

        int root(int i)
        {
            auto old_i = i;
            while (parent[i] != i)
            {
                i = parent[i];
            }

            while (parent[old_i] != i)
            {
                old_i = parent[old_i];
                parent[old_i] = i;
            }

            return i;
        }

        std::vector<int> parent;
    };

    // 132 ms, faster than 74.80%. 50.4 MB, less than 30.41% of C++ 
    std::vector<std::vector<std::string>> accountsMerge_dfs(std::vector<std::vector<std::string>>& accounts)
    {
        if (accounts.size() <= 1)
            return accounts;

        // build graph
        std::unordered_map<std::string, std::string> email2name;
        std::unordered_map<std::string, std::vector<std::string>> adj_list;
        for (const auto& ac : accounts)
        {
            const auto N = static_cast<int>(ac.size());
            if (N < 2)
                continue;

            const auto& name = ac[0];
            const auto& first_email = ac[1];
            if (adj_list.find(first_email) == adj_list.end())
                adj_list.insert({ first_email, {} });
            email2name[first_email] = name;
            for (auto i = 2; i < N; ++i)
            {
                adj_list[first_email].push_back(ac[i]);
                adj_list[ac[i]].push_back(first_email);
                email2name[ac[i]] = name;
            }
        }

        // run DFS
        std::vector<std::vector<std::string>> res;
        std::unordered_set<std::string> visited;
        for (const auto& p : adj_list)
        {
            const auto& vertex = p.first;
            if (visited.find(vertex) != visited.end())
                continue;

            std::stack<std::string> stk;
            visited.insert(vertex);
            stk.push(vertex);
            std::vector<std::string> component{email2name[vertex]};
            while (!stk.empty())
            {
                const auto curr = stk.top();
                stk.pop();
                component.push_back(curr);
                const auto& neighbors = adj_list[curr];
                for (const auto& n : neighbors)
                {
                    if (visited.find(n) == visited.end())
                    {
                        visited.insert(n);
                        stk.push(n);
                    }
                }
            }

            // sort e-mails
            std::sort(component.begin() + 1, component.end());
            res.push_back(std::move(component));
        }

        return res;
    }

    std::vector<std::vector<std::string>> accountsMerge_naive_incorrect(std::vector<std::vector<std::string>>& accounts)
    {
        if (accounts.size() <= 1)
            return accounts;

        using name2email_t = std::pair < std::string, std::set<std::string> >;
        std::list<name2email_t> lst;
        for (const auto& ac : accounts)
        {
            if (ac.size() < 2)
                continue;

            std::set<std::string> s(ac.begin() + 1, ac.end());
            lst.emplace_back(ac[0], std::move(s));
        }

        for (auto itr = lst.begin(); itr != lst.end(); ++itr)
        {
            auto itr_to_merge = itr;
            ++itr_to_merge;
            while(itr_to_merge != lst.end())
            {
                if (itr->first != itr_to_merge->first)
                {
                    ++itr_to_merge;
                    continue;
                }

                auto need_to_merge = false;
                for (const auto& str : itr->second)
                {
                    need_to_merge |= (itr_to_merge->second.find(str) != itr_to_merge->second.end());
                    if (need_to_merge)
                        break;
                }

                if (need_to_merge)
                {
                    itr->second.insert(itr_to_merge->second.cbegin(), itr_to_merge->second.cend());
                    itr_to_merge = lst.erase(itr_to_merge);
                }
                else
                    ++itr_to_merge;
            }
        }

        std::vector<std::vector<std::string>> res;
        res.reserve(lst.size());
        for (const auto& l : lst)
        {
            std::vector<std::string> ac;
            ac.push_back(l.first);
            ac.insert(ac.end(), l.second.begin(), l.second.end());
            res.push_back(std::move(ac));
        }

        return res;
    }
};
}

void AccountsMerge()
{
    Solution sol;
    std::vector<std::vector<std::string>> accounts{ {"David", "David0@m.co", "David1@m.co"}, 
                                                    {"David", "David3@m.co", "David4@m.co"}, 
                                                    {"David", "David4@m.co", "David5@m.co"}, 
                                                    {"David", "David2@m.co", "David3@m.co"}, 
                                                    {"David", "David1@m.co", "David2@m.co"} };
    std::vector<std::vector<std::string>> expected{ {"David", "David0@m.co", "David1@m.co", "David2@m.co", "David3@m.co", "David4@m.co", "David5@m.co"} };
    auto merged = sol.accountsMerge(accounts);  
    assert(merged == expected);

    accounts = {{"John", "johnsmith@mail.com", "john00@mail.com"},
                {"John", "johnnybravo@mail.com"}, 
                {"John", "johnsmith@mail.com", "john_newyork@mail.com"}, 
                {"Mary", "mary@mail.com"}};
    expected = {{"John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"},
                {"John", "johnnybravo@mail.com"},
                {"Mary", "mary@mail.com"}};
    merged = sol.accountsMerge(accounts);
    assert(merged == expected);

    accounts = {{"Alex", "Alex5@m.co", "Alex4@m.co", "Alex0@m.co"}, 
                {"Ethan", "Ethan3@m.co", "Ethan3@m.co", "Ethan0@m.co"}, 
                {"Kevin", "Kevin4@m.co", "Kevin2@m.co", "Kevin2@m.co"}, 
                {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe2@m.co"}, 
                {"Gabe", "Gabe3@m.co", "Gabe4@m.co", "Gabe2@m.co"}};
    expected = {{"Alex", "Alex0@m.co", "Alex4@m.co", "Alex5@m.co"}, 
                {"Ethan", "Ethan0@m.co", "Ethan3@m.co"}, 
                {"Gabe", "Gabe0@m.co", "Gabe2@m.co", "Gabe3@m.co", "Gabe4@m.co"}, 
                {"Kevin", "Kevin2@m.co", "Kevin4@m.co"}};
    merged = sol.accountsMerge(accounts);
    std::sort(merged.begin(), merged.end(), [](const auto& lhs_v, const auto& rhs_v) {return lhs_v[0] < rhs_v[0]; });
    assert(merged == expected);
}