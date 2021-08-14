#include <string>
#include <cassert>
#include <vector>

//#define DEBUG_INFO
#ifdef DEBUG_INFO
#include <iostream>
#endif

namespace
{
class Solution 
{
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) 
    {
        //return brute_force(s1, s2, s3);
        //return improved_brute_force(s1, s2, s3);
        //return recursive_memorization(s1, s2, s3);
        return dp(s1, s2, s3);
    }

private:
    bool dp(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        const auto N1 = static_cast<int>(s1.size());
        const auto N2 = static_cast<int>(s2.size());
        const auto N3 = static_cast<int>(s3.size());

        if (N1 + N2 != N3)
            return false;

        std::vector< std::vector<bool> > dp(N1 + 1, std::vector<bool>(N2 + 1, false));
        for (auto i = 0; i <= N1; ++i)
        {
            for (auto j = 0; j <= N2; ++j)
            {
                if (0 == i && 0 == j)
                {
                    dp[i][j] = true;
                }
                else if (0 == i)
                {
                    dp[i][j] = (s3[i + j - 1] == s2[j - 1]) && dp[i][j - 1];
                }
                else if (0 == j)
                {
                    dp[i][j] = (s3[i + j - 1] == s1[i - 1]) && dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = ((s3[i + j - 1] == s1[i - 1]) && dp[i-1][j])
                             ||((s3[i + j - 1] == s2[j - 1]) && dp[i][j-1]);
                }
            }
        }

        return dp[N1][N2];
    }

    bool recursive_memorization(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        m_N1 = static_cast<int>(s1.size());
        m_N2 = static_cast<int>(s2.size());
        const auto N3 = static_cast<int>(s3.size());
        m_s3 = s3;

        if (m_N1 + m_N2 != N3)
            return false;

        m_already_visited = std::vector<std::vector<char>>(m_N1+1, std::vector<char>(m_N2+1, -1));

        return recursive_memorization_impl(s1, 0, s2, 0);
    }

    bool recursive_memorization_impl(const std::string& s1, int i, const std::string& s2, int j)
    {
#ifdef DEBUG_INFO
        std::cout << "i = " << i << "; j = " << j << "\n";
#endif
        if (m_already_visited[i][j] >= 0)
        {
            return static_cast<bool>(m_already_visited[i][j]);
        }

        if (i == m_N1 && j == m_N2)
        {
            m_already_visited[i][j] = 1;
            return true;
        }

        if (i == m_N1)
        {
            for (; i + j < m_N1 + m_N2; ++j)
            {
                if (s2[j] != m_s3[i + j])
                {
                    m_already_visited[i][j] = 0;
                    return false;
                }
            }

            m_already_visited[i][j] = 1;
            return true;
        }

        if (j == m_N2)
        {
            for (; i + j < m_N1 + m_N2; ++i)
            {
                if (s1[i] != m_s3[i + j])
                {
                    m_already_visited[i][j] = 0;
                    return false;
                }
            }

            m_already_visited[i][j] = 1;
            return true;
        }

        const auto next_char = m_s3[i + j];
        if (s1[i] != next_char && s2[j] != next_char)
        {
            m_already_visited[i][j] = 0;
            return false;
        }

        bool res;
        if (s1[i] != next_char)
        {
            res = recursive_memorization_impl(s1, i, s2, j + 1);
            m_already_visited[i][j] = static_cast<char>(res);
            return res;
        }

        if (s2[j] != next_char)
        {
            res = recursive_memorization_impl(s1, i + 1, s2, j);
            m_already_visited[i][j] = static_cast<char>(res);
            return res;
        }

        res = recursive_memorization_impl(s1, i + 1, s2, j) || recursive_memorization_impl(s1, i, s2, j + 1);
        m_already_visited[i][j] = static_cast<char>(res);
        return res;
    }

    bool improved_brute_force(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        m_N1 = static_cast<int>(s1.size());
        m_N2 = static_cast<int>(s2.size());
        const auto N3 = static_cast<int>(s3.size());
        m_s3 = s3;

        if (m_N1 + m_N2 != N3)
            return false;

        return improved_bf(s1, 0, s2, 0);
    }

    bool improved_bf(const std::string& s1, int i, const std::string& s2, int j)
    {
#ifdef DEBUG_INFO
        std::cout << "i = " << i << "; j = " << j << "\n";
#endif
        if (i == m_N1 && j == m_N2)
            return true;

        if (i == m_N1)
        {
            for (; i + j < m_N1 + m_N2; ++j)
            {
                if (s2[j] != m_s3[i + j])
                    return false;
            }

            return true;
        }

        if (j == m_N2)
        {
            for (; i + j < m_N1 + m_N2; ++i)
            {
                if (s1[i] != m_s3[i + j])
                    return false;
            }

            return true;
        }

        const auto next_char = m_s3[i + j];
        if (s1[i] != next_char && s2[j] != next_char)
        {
            return false;
        }

        if (s1[i] != next_char)
        {
            return improved_bf(s1, i, s2, j + 1);
        }

        if (s2[j] != next_char)
        {
            return improved_bf(s1, i + 1, s2, j);
        }

        return improved_bf(s1, i + 1, s2, j) || improved_bf(s1, i, s2, j + 1);
    }

    bool brute_force(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        m_N1 = static_cast<int>(s1.size());
        m_N2 = static_cast<int>(s2.size());
        const auto N3 = static_cast<int>(s3.size());
        m_s3 = s3;

        if (m_N1 + m_N2 != N3)
            return false;

        std::string res;
        return bf_recurcive(s1, 0, s2, 0, res);
    }

    bool bf_recurcive(const std::string& s1, int i, const std::string& s2, int j, std::string res)
    {
#ifdef DEBUG_INFO
        std::cout << "i = " << i << "; j = " << j << "\n";
#endif
        if (i == m_N1 && j == m_N2)
        {
            return res == m_s3;
        }

        if (i == m_N1)
            return bf_recurcive(s1, i, s2, j + 1, res + s2[j]);

        if (j == m_N2)
            return bf_recurcive(s1, i + 1, s2, j, res + s1[i]);

        return bf_recurcive(s1, i + 1, s2, j, res + s1[i]) || bf_recurcive(s1, i, s2, j + 1, res + s2[j]);
    }

    int m_N1;
    int m_N2;
    std::string m_s3;

    std::vector<std::vector<char>> m_already_visited;
};
}

void InterleavingString()
{
    std::string s1 = "abc";
    std::string s2 = "bcd";
    std::string s3 = "abcbdc";
    Solution sol;
    auto res = sol.isInterleave(s1, s2, s3);
    assert(res == true);
#ifdef DEBUG_INFO
    std::cout << "\n";
#endif

    s1 = "aaa";
    s2 = "aaaa";
    s3 = "aaaaaaa";
    res = sol.isInterleave(s1, s2, s3);
    assert(res == true);
#ifdef DEBUG_INFO
    std::cout << "\n";
#endif

    s1 = "aabcc";
    s2 = "dbbca";
    s3 = "aadbbcbcac";
    res = sol.isInterleave(s1, s2, s3);
    assert(res == true);
#ifdef DEBUG_INFO
    std::cout << "\n";
#endif

    s1 = "bbbcc";
    s2 = "bbaccbbbabcacc";
    s3 = "bbbbacbcccbcbabbacc";
    res = sol.isInterleave(s1, s2, s3);
    assert(res == false);
#ifdef DEBUG_INFO
    std::cout << "\n";
#endif

    s1 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
    s2 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
    s3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";
    res = sol.isInterleave(s1, s2, s3);
    assert(res == false);
#ifdef DEBUG_INFO
    std::cout << "\n";
#endif
}