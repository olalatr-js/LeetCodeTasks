#include <string>
#include <vector>
#include <cassert>

namespace
{
class Solution
{
public:
    int numDecodings(std::string s)
    {
        const auto N = static_cast<int>(s.size());
        if (s[0] == '0')
            return 0;

        if (N == 1)
            return 1;

        std::vector<int> dp(N + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (auto i = 2; i <= N; ++i)
        {
            // If the last digit is not 0,
            // then last digit must add to the number of words
            if (s[i - 1] > '0')
                dp[i] = dp[i - 1];

            // If second last digit is smaller
            // than 2 and last digit is smaller than 7,
            // then last two digits form a valid character
            if (s[i - 2] == '1' ||
                (s[i - 2] == '2' && s[i - 1] < '7'))
                dp[i] += dp[i - 2];
        }

        return dp[N];
    }

private:
    int numDecodings_incorrect(std::string s)
    {
        const auto N = static_cast<int>(s.size());
        if (s[0] == '0')
            return 0;

        if (N == 1)
            return 1;

        std::vector<int> dp(N + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (auto i = 2; i <= N; ++i)
        {
            if (s[i - 1] == '0')
            {
                if (!(s[i - 2] == '1' || s[i - 2] == '2'))
                    return 0;

                dp[i] = dp[i - 1];
            }
            else
            {
                const auto num = 10 * (s[i - 2] - '0') + (s[i - 1] - '0');
                if (num == 1 || num == 2)
                {
                    dp[i] = dp[i - 2];
                }
                else if (10 < num && num <= 26)
                    dp[i] = dp[i - 1] + dp[i - 2];
                else
                    dp[i] = dp[i - 1];
            }
        }

        return dp[N];
    }
};
}

void DecodeWays()
{
    Solution sol;
    std::string s;
    int res;

    s = "123";
    res = sol.numDecodings(s);
    assert(3 == res);

    s = "2101";
    res = sol.numDecodings(s);
    assert(1 == res);

    s = "121";
    res = sol.numDecodings(s);
    assert(3 == res);

    s = "132";
    res = sol.numDecodings(s);
    assert(2 == res);

    s = "1232122323122313";
    res = sol.numDecodings(s);
    assert(480 == res);

    s = "234325345236789768054";
    res = sol.numDecodings(s);
    assert(0 == res);

    s = "121212";
    res = sol.numDecodings(s);
    assert(13 == res);

    s = "123213";
    res = sol.numDecodings(s);
    assert(9 == res);
}