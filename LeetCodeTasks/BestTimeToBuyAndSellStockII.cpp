#include <vector>

namespace
{
class Solution
{
public:
    int maxProfit(std::vector<int>& prices)
    {
        const auto N = static_cast<int>(prices.size());
        if (N <= 1)
            return 0;

        auto total_profit = 0;
        auto i = 1;
        while (i < N)
        {
            // go to local minimum
            while (i < N && prices[i - 1] >= prices[i])
                ++i;
            auto loc_min = prices[i - 1];

            // go to local maximum
            while (i < N && prices[i - 1] <= prices[i])
                ++i;
            auto loc_max = prices[i - 1];

            total_profit += loc_max - loc_min;

        }

        return total_profit;
    }
};
}

void BestTimeToBuyAndSellStockII()
{

}