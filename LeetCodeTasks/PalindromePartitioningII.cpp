#include <string>
#include <vector>
#include <algorithm>

namespace
{
class Solution 
{
public:
    int minCut(std::string s) 
    {
        m_N = static_cast<int>(s.size());
        const auto is_pal = prepare(s);
        std::vector<int> dp(m_N);

        for (auto end = 0; end < m_N; ++end)
        {
            auto cuts_num = end;
            for (auto start = 0; start <= end; ++start)
            {
                if (is_pal[start][end])
                {
                    if (start == 0)
                        cuts_num = 0;
                    else
                    {
                        cuts_num = std::min(cuts_num, dp[start - 1] + 1);
                        // number of min cuts for [0, start-1] interval + 1 cut between start - 1 and start positions.
                        // [start, end] is palindrome
                    }
                }
            }

            dp[end] = cuts_num;
        }

        return dp[m_N - 1];
    }

private:
    std::vector< std::vector<bool> > prepare(const std::string& str)
    {
        std::vector< std::vector<bool> > res(m_N, std::vector<bool>(m_N, false));
        for (auto start = m_N - 1; start >= 0; --start)
        {
            for (auto end = start; end < m_N; ++end)
            {
                if (start == end)
                    res[start][end] = true;
                else
                {
                    res[start][end] = (str[start] == str[end]);
                    if (start + 1 < end - 1)
                        res[start][end] = res[start][end] && res[start + 1][end - 1];
                }
            }
        }

        return res;
    }

    std::vector< std::vector<bool> > m_is_pal;
    int m_N;
};
}

void PalindromePartitioningII()
{

}