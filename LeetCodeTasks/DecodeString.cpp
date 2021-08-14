#include <string>
#include <tuple>
#include <stdexcept>
#include <cassert>

namespace
{
class Solution 
{
public:
    std::string decodeString(std::string s) 
    {
        const auto N = s.size();
        return decode_string(s, 0, s.size());
    }

private:
    std::string decode_string(const std::string& str, int beg, int end)
    {
        std::string res;
        while (beg < end)
        {
            while (is_letter(str[beg]))
            {
                res += str[beg];
                ++beg;
            }

            if (beg == end)
                return res;

            int num;
            int end_nested;
            std::tie(num, beg) = read_number(str, beg);
            end_nested = determine_nested_str_pos(str, beg);

            const auto nested_str = decode_string(str, beg + 1, end_nested - 1);
            for (auto i = 0; i < num; ++i)
            {
                res += nested_str;
            }

            beg = end_nested;
        }

        return res;
    }

    bool is_letter(const char ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    std::tuple<int, int> read_number(const std::string& str, int beg)
    {
        int digits_num = 0;
        auto number_end = beg;
        while (str[number_end] >= '0' && str[number_end] <= '9')
        {
            ++digits_num;
            ++number_end;
        }

        int num = 0;
        int pow10 = 1; // 10^0
        for (int i = number_end - 1; i >= beg; --i)
        {
            num += (str[i] - '0') * pow10;
            pow10 *= 10;
        }

        return { num, number_end };
    }

    int determine_nested_str_pos(const std::string& str, int beg)
    {
        if (str[beg] != '[')
            throw std::invalid_argument("Expect to see [");
        auto balance = 1;
        ++beg;
        while (balance)
        {
            if (str[beg] == '[')
                ++balance;
            if (str[beg] == ']')
                --balance;
            ++beg;
        }

        return beg;
    }
};
}

void DecodeString()
{
    Solution sol;
    std::string s = "3[a]2[bc]";
    auto res = sol.decodeString(s);
    assert(res == "aaabcbc");
}