#include <vector>
#include <algorithm>
#include <cassert>

namespace
{
class Solution
{
public:
    // dp[k, i] = max(dp[k, i-1], prices[i] - prices[j] + dp[k-1, j-1]), j=[0..i-1]
    // For k transactions, on i-th day,
    // if we don't trade then the profit is same as previous day dp[k, i-1];
    // and if we bought the share on j - th day where j = [0..i - 1], then sell the share on i - th day then the profit is prices[i] - prices[j] + dp[k - 1, j - 1] .
    int maxProfit(std::vector<int>& prices)
    {
        const auto N = static_cast<int>(prices.size());
        if (N <= 1)
            return 0;

        std::vector<std::vector<int>> dp(2, std::vector<int>(N, 0));
        // dp[k][i] profit on with k+1 finished transactions and day i
        // dp[0][i] profit with 1 finished transaction on day i
        auto prev_seen_min = prices[0];
        for (auto i = 1; i < N; ++i)
        {
            prev_seen_min = std::min(prices[i], prev_seen_min);
            dp[0][i] = std::max(dp[0][i-1], prices[i] - prev_seen_min);
        }

        // dp[1][i] profit with 1 or 2 finished transactions on day i
        auto buy2 = prices[0];
        for (auto i = 1; i < N; ++i)
        {
            // Because of this fragment Time Limit Exceeded
            //auto min_j = prices[0];
            //for (auto j = 1; j < i; ++j)
            //{
            //    min_j = std::min(min_j, prices[j] - dp[0][j - 1]);
            //}

            //Improved fragment min_j = buy2 = (current price) - (profit from the previous sale) 
            buy2 = std::min(buy2, prices[i] - dp[0][i-1]);

            dp[1][i] = std::max(dp[1][i - 1], // do not sell on day i
                // sell on day i stock bought on day j + profit from the previous transaction
                prices[i] - buy2);
        }

        return dp[1][N - 1];
    }

private:
    int maxProfit_wrong_answer(std::vector<int>& prices)
    {
        const auto N = static_cast<int>(prices.size());
        if (N <= 1)
            return 0;

        std::vector<int> local_profits;
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

            if (loc_max > loc_min)
                local_profits.push_back(loc_max - loc_min);
        }

        auto two_trans_profit = 0;
        std::sort(local_profits.begin(), local_profits.end());
        auto trans_num = 0;
        auto itr = local_profits.rbegin();
        while (itr != local_profits.rend() && trans_num < 2)
        {
            two_trans_profit += *itr;
            ++itr;
            ++trans_num;
        }

        return two_trans_profit;
    }
};
}

void BestTimeToBuyAndSellStockIII()
{
    Solution sol;
    std::vector<int> prices;
    int res;

    prices = { 3, 3, 5, 0, 0, 3, 1, 4 };
    res = sol.maxProfit(prices);
    assert(6 == res);

    prices = {1, 2, 3, 4, 5}; 
    res = sol.maxProfit(prices);
    assert(4 == res);

    prices = {7, 6, 4, 3, 1}; 
    res = sol.maxProfit(prices);
    assert(0 == res);

    prices = {1}; 
    res = sol.maxProfit(prices);
    assert(0 == res);

    prices = { 1,2,4,2,5,7,2,4,9,0 };
    res = sol.maxProfit(prices);
    assert(13 == res);
}