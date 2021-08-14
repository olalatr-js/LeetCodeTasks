#include <string>
#include <unordered_map>
#include <algorithm>

namespace
{
class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        std::unordered_map<char, int> ch2pos;
        const auto N = static_cast<int>(s.size());
        auto start = 0;
        auto max_len = 1;
        for (auto end = 0; end < N; ++end)
        {
            if (ch2pos.find(s[end]) != ch2pos.end())
            {
                start = ch2pos[s[end]] + 1;
            }

            ch2pos[s[end]] = end;

            max_len = std::max(max_len, end - start + 1);
        }

        return max_len;
    }
};
}

void LongestSubstringWithoutRepeatingCharacters()
{

}