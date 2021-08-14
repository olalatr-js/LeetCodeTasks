#include <vector>
#include <numeric>
#include <algorithm>

namespace
{
class Solution 
{
public:
    int candy(std::vector<int>& ratings)
    {
        const auto N = static_cast<int>(ratings.size());
        std::vector<int> candies(N, 1);
        // move left to right
        for (auto i = 1; i < N; ++i)
        {
            if (ratings[i - 1] < ratings[i])
                candies[i] = 1 + candies[i - 1];
        }

        // move right to left
        for (auto j = N - 2; j >= 0; --j)
        {
            if (ratings[j] > ratings[j + 1])
                candies[j] = std::max(candies[j], 1 + candies[j+1]);
        }

        return std::accumulate(candies.cbegin(), candies.cend(), 0);
    }

    // TLE
    int candy_TLE(std::vector<int>& ratings) 
    {
        const auto N = static_cast<int>(ratings.size());
        std::vector<int> candies(N, 1);
        for (auto i = 1; i < N; ++i)
        {
            if (ratings[i - 1] < ratings[i])
            {
                candies[i] = 1 + candies[i - 1];
            }
            else
            {
                auto j = i;
                while (j > 0 && ratings[j - 1] > ratings[j] && candies[j - 1] <= candies[j])
                {
                    candies[j - 1] = 1 + candies[j];
                    --j;
                }
            }
        }

        const auto sum = std::accumulate(candies.begin(), candies.end(), 0);
        return sum;
    }
};
}

void Candy()
{

}