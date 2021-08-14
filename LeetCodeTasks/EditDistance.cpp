#include <string>
#include <vector>
#include <algorithm>

namespace
{
class Solution 
{
public:
    int minDistance(std::string word1, std::string word2) 
    {
        const auto M = static_cast<int>(word1.size());
        const auto N = static_cast<int>(word2.size());
        if (0 == M)
            return N;
        if (0 == N)
            return M;

        std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));
        for (auto i = 0; i < M; ++i)
        {
            for (auto j = 0; j < N; ++j)
            {
                if (0 == i)
                {
                    dp[i][j] = j + 1;
                    continue;
                }

                if (0 == j)
                {
                    dp[i][j] = i + 1;
                    continue;
                }

                if (word1[i] == word2[j])
                {
                    dp[i][j] = dp[i-1][j-1];
                    continue;
                }

                dp[i][j] = 1 + std::min(std::min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
            }
        }

        return dp[M-1][N-1];
    }
};
}

void EditDistance()
{

}