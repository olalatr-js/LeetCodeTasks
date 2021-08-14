#include <cassert>
namespace
{
class Solution
{
public:
    int climbStairs(int n)
    {
        m_N = n;
        m_res = 0;
        recursive(1);
        recursive(2);

        return m_res;
    }
private:
    void recursive(int count)
    {
        if (count > m_N)
            return;

        if (count == m_N)
        {
            ++m_res;
            return;
        }

        recursive(count + 1);
        recursive(count + 2);
    }

    int m_N;
    int m_res;
};
}

void ClimbingStairs()
{
    Solution sol;

    auto n = 2;
    auto res = sol.climbStairs(n);
    assert(res == 2);

    n = 3;
    res = sol.climbStairs(n);
    assert(res == 3);

    n = 17;
    res = sol.climbStairs(n);
    assert(res == 2584);

    n = 40;
    res = sol.climbStairs(n);
    assert(res == 165580141);
}