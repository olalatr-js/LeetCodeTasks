#include <vector>
#include <algorithm>
#include <cassert>

namespace
{
class Solution
{
public:
    int maxProfit(int k, std::vector<int>& prices)
    {
        const auto N = static_cast<int>(prices.size());
        if (N <= 1 || k == 0)
            return 0;

        std::vector<std::vector<int>> buy(k, std::vector<int>(N, 0));
        std::vector<std::vector<int>> sell(k, std::vector<int>(N, 0));
        for (auto j = 0; j < k; ++j)
            buy[j][0] = prices[0];

        for (auto i = 1; i < N; ++i)
        {
            buy[0][i] = std::min(buy[0][i - 1], prices[i]);
            sell[0][i] = std::max(sell[0][i - 1], prices[i] - buy[0][i]);
        }

        for (auto i = 1; i < N; ++i)
        {
            for (auto j = 1; j < k; ++j)
            {
                buy[j][i] = std::min(buy[j][i - 1], prices[i] - sell[j - 1][i - 1]);
                sell[j][i] = std::max(sell[j][i - 1], prices[i] - buy[j][i]);
            }
        }

        return sell[k - 1][N - 1];
    }
};
}

void BestTimeToBuyAndSellStockIV()
{
    Solution sol;
    int k;
    std::vector<int> prices;
    int res;

    k = 2;
    prices = { 2, 4, 1 };
    res = sol.maxProfit(k, prices);
    assert(2 == res);
}