#include <stack>
#include <string>
#include <stdexcept>
#include <cassert>

namespace
{
class Solution
{
public:
    int calculate(std::string s)
    {
        const auto N = static_cast<int>(s.size());
        auto i = 0;

        // scan string
        while (i < N)
        {
            if (s[i] == ' ')
            {
                ++i;
                continue;
            }

            if (is_number(s[i]))
            {
                int num = 0;
                while (i < N && is_number(s[i]))
                {
                    num = 10 * num + (s[i] - '0');
                    ++i;
                }

                m_operands.push(num);
            }
            else if (is_operator(s[i]))
            {
                if (s[i] == '(')
                    m_operators.push(s[i]);
                else if (s[i] == ')')
                {
                    // evalute till previous ( in the stack
                    while (m_operators.top() != '(')
                    {
                        do_one_operation();
                    }

                    m_operators.pop(); // pop '(''
                }
                else
                {
                    while (!m_operators.empty() && (pres(s[i]) <= pres(m_operators.top())))
                    {
                        do_one_operation();
                    }

                    m_operators.push(s[i]);
                }

                ++i;
            }
            else
            {
                throw std::invalid_argument("Input string must contain either numbers or operands or white spaces");
            }
        }

        // process stacks
        while (!m_operators.empty())
        {
            do_one_operation();
        }

        //if (m_operands.size() != 1)
        //    throw std::logic_error("Operands stack must contain only one element with answer");

        return m_operands.top();
    }

private:
    void do_one_operation()
    {
        const auto opr = m_operators.top();
        m_operators.pop();

        const auto arg2 = m_operands.top();
        m_operands.pop();

        const auto arg1 = m_operands.top();
        m_operands.pop();

        const auto res = evaluate(opr, arg1, arg2);
        m_operands.push(res);
    }

    int pres(const char ch)
    {
        if (ch == '+' || ch == '-')
            return 1;
        if (ch == '*' || ch == '/')
            return 2;

        throw std::invalid_argument("Unsupported type of operator");
    }

    bool is_operator(const char ch)
    {
        if (ch == '(' || ch == ')' ||
            ch == '+' || ch == '-' ||
            ch == '*' || ch == '/')
        {
            return true;
        }

        return false;
    }

    bool is_number(const char ch)
    {
        return ('0' <= ch) && (ch <= '9');
    }

    int evaluate(char opr, int arg1, int arg2)
    {
        switch (opr)
        {
        case '+': return arg1 + arg2;
        case '-': return arg1 - arg2;
        case '*': return arg1 * arg2;
        case '/': return arg1 / arg2;
        default: throw std::invalid_argument("Unsupported evaluation");
        }
    }

    std::stack<int> m_operands;
    std::stack<char> m_operators;
};
}

void BasicCalculatorII()
{
    Solution sol;
    std::string s;
    int res;

    s = "1337";
    res = sol.calculate(s);
    assert(res == 1337);

    s = " 1 +2-3*4*5 -7/2";
    res = sol.calculate(s);
    assert(res == -60);

    s = " 1 +2-3*4*5 -7/2-2 * 4 +9";
    res = sol.calculate(s);
    assert(res == -59);
}