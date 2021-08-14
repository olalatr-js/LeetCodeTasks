#include <vector>
#include <string>
#include <cassert>

namespace
{
// Runtime: 120 ms, faster than 57.27% of C++ online submissions for Palindrome Partitioning.
// Memory Usage : 97.2 MB, less than 33.25 % of C++ online submissions for Palindrome Partitioning.
class Solution_1
{
public:
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        m_N = static_cast<int>(s.size());
        std::vector<std::string> cand;
        m_res.clear();
        dfs(s, 0, cand);
        return m_res;
    }

private:
    void dfs(const std::string& s, int pos, std::vector<std::string>& cand)
    {
        if (pos >= m_N)
        {
            if (all_palindromes(cand))
                m_res.push_back(cand);

            return;
        }

        cand.push_back(std::string(1, s[pos]));
        dfs(s, pos + 1, cand);
        cand.pop_back();

        if (!cand.empty())
        {
            cand.back().push_back(s[pos]);
            dfs(s, pos + 1, cand);
            cand.back().pop_back();
        }
    }

    bool all_palindromes(const std::vector<std::string>& cand)
    {
        for (const auto& str : cand)
        {
            if (!is_palindrome(str))
                return false;
        }

        return true;
    }

    bool is_palindrome(const std::string& str)
    {
        const auto N = static_cast<int>(str.size());
        auto i = 0, j = N - 1;
        while (i < j)
        {
            if (str[i] != str[j])
                return false;
            ++i;
            --j;
        }

        return true;
    }

    int m_N;
    std::vector<std::vector<std::string>> m_res;
};

// Runtime: 116 ms, faster than 62.08 % of C++ online submissions for Palindrome Partitioning.
// Memory Usage : 75.7 MB, less than 50.14 % of C++ online submissions for Palindrome Partitioning.
class Solution
{
public:
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        m_N = static_cast<int>(s.size());
        m_dp = build_table(s);

        std::vector<std::string> cand;
        m_res.clear();
        dfs(s, 0, cand);
        return m_res;
    }

private:
    void dfs(const std::string& s, int pos, std::vector<std::string>& cand)
    {
        if (pos >= m_N)
        {
            m_res.push_back(cand);
            return;
        }

        for (auto i = pos; i < m_N; ++i)
        {
            if (m_dp[pos][i])
            {
                cand.push_back(s.substr(pos, i - pos + 1));

                dfs(s, i + 1, cand);

                // back track
                cand.pop_back();
            }
        }
    }

    std::vector<std::vector<int>> build_table(const std::string& s)
    {
        std::vector<std::vector<int>> table(m_N, std::vector<int>(m_N, false));
        for (auto i = m_N - 1; i >= 0; --i)
        {
            for (auto j = i; j < m_N; ++j)
            {
                if (i == j)
                {
                    table[i][j] = true;
                }
                else
                {
                    table[i][j] = (s[i] == s[j]);
                    if (i + 1 < j - 1)
                        table[i][j] = table[i][j] && table[i + 1][j - 1];
                }
            }
        }
        return table;
    }

    int m_N;
    std::vector<std::vector<int>> m_dp;
    std::vector<std::vector<std::string>> m_res;
};
}

void PalindromePartitioning()
{
    Solution sol;
    std::string s;
    std::vector<std::vector<std::string>> res;
    std::vector<std::vector<std::string>> expected;

    s = "aab";
    res = sol.partition(s);
    expected = { {"a", "a", "b"}, {"aa", "b"} };
    assert(res == expected);

    s = "efe";
    res = sol.partition(s);
    expected = { {"e", "f", "e"},{"efe"} };
    assert(res == expected);

    s = "fff";
    res = sol.partition(s);
    expected = { {"f", "f", "f"}, {"f", "ff"}, {"ff", "f"}, {"fff"} };
    assert(res == expected);

    s = "abbab";
    res = sol.partition(s);
    expected = { {"a", "b", "b", "a", "b"}, {"a", "b", "bab"}, {"a", "bb", "a", "b"}, {"abba", "b"} };
    assert(res == expected);
}