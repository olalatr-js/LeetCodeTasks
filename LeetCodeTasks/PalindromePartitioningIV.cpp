#include <string>
#include <vector>

namespace
{
class Solution
{
public:
    bool checkPartitioning(std::string s)
    {
        m_N = static_cast<int>(s.size());
        const auto is_pal = prepare(s);

        // [0, m_N-1] = [0, cut1 - 1] U [cut1, cut2 - 1] U [cut2, m_N - 1]
        for (auto cut1 = 1; cut1 < m_N - 1; ++cut1)
        {
            if (!is_pal[0][cut1 - 1])
                continue;

            for (auto cut2 = cut1; cut2 < m_N; ++cut2)
            {
                if (is_pal[cut1][cut2 - 1] && is_pal[cut2][m_N - 1])
                    return true;
            }
        }

        return false;
    }

private:
    std::vector<std::vector<bool>> prepare(const std::string& s)
    {
        std::vector<std::vector<bool>> res(m_N, std::vector<bool>(m_N, false));
        for (auto start = m_N - 1; start >= 0; --start)
        {
            for (auto end = start; end < m_N; ++end)
            {
                if (start == end)
                {
                    res[start][end] = true;
                }
                else
                {
                    res[start][end] = (s[start] == s[end]) &&
                        (end - start < 2 || res[start + 1][end - 1]);
                }
            }
        }

        return res;
    }

    int m_N;
};
}

void PalindromePartitioningIV()
{

}