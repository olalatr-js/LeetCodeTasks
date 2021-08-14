#include <string>
#include <vector>
#include <cassert>

namespace
{
class Solution 
{
public:
    std::string longestPrefix(std::string s)
    {
        const auto N = static_cast<int>(s.size());
        if (N <= 1)
            return {};

        std::vector<int> lps(N);
        lps[0] = 0;
        auto i = 1;
        auto len = 0; // lenght of the longest valid prefix - suffix
        while (i < N)
        {
            if (s[i] == s[len])
            {
                ++len;
                lps[i] = len;
                ++i;
            }
            else
            {
                if (len == 0)
                {
                    lps[i] = 0;
                    ++i;
                }
                else
                {
                    len = lps[len - 1];
                }
            }
        }

        const auto max_suf_len = lps[N - 1];
        return s.substr(0, max_suf_len);
    }

private:
    // solution based on hash sums calculation
    std::string longestPrefix_accepted(std::string s)
    {
        const auto N = static_cast<int>(s.size());
        if (N <= 1)
            return {};

        using data_t = unsigned int;
        constexpr data_t R = 26;
        constexpr data_t modulo = 1000003;
        data_t suf_hash = 0;
        data_t pref_hash = 0;
        std::vector<data_t> pref_hashes(N-1);
        std::vector<data_t> suf_hashes(N-1);

        // prefix hash for interval [0; i], i in [0, (N-2)]    
        for (auto i = 0; i < N - 1; ++i)
        {
            pref_hash = (pref_hash*R + (s[i] - 'a')) % modulo;
            pref_hashes[i] = pref_hash;
        }

        // suffix hash for interval [j; N-1]. j in [1; N-1]
        data_t R_pow = 1;
        for (auto j = N - 1; j >= 1; --j)
        {
            suf_hash = (R_pow * (s[j] - 'a') + suf_hash) % modulo;
            suf_hashes[N - 1 - j] = suf_hash;

            R_pow = (R * R_pow) % modulo;
        }

        for (auto j = N-2; j >= 0; --j)
        {
            if (pref_hashes[j] == suf_hashes[j])
            {
                if (compare(s, 0, j + 1, N - j - 1))
                    return s.substr(0, j + 1);
            }
        }

        return {};
    }

    std::string longestPrefix_can_not_devide(std::string s) 
    {
        //  1 <= s.length <= 105
        //  s contains only lowercase English letters.
        const auto N = static_cast<int>(s.size());
        if (N == 1)
        {
            return {};
        }

        using data_t = int;
        constexpr data_t R = 26;
        constexpr data_t modulo = 1000003;
        

        std::vector<data_t> R_powers(N);
        R_powers[0] = 1;
        data_t pref_hash = 0;
        data_t suf_hash = 0;

        // calculate the longest possible prefix, sufix
        // interval for prefix [0; i]
        // interval for suffix [1; i+1]
        for (auto i = 0; i < N - 1; ++i)
        {
            pref_hash = ( pref_hash*R + (static_cast<data_t>(s[i]) - 'a') ) % modulo;
            suf_hash = (suf_hash * R + (static_cast<data_t>(s[i + 1]) - 'a')) % modulo;
            R_powers[i + 1] = (R_powers[i] * R) % modulo;
        }

        for (auto pref_idx = N - 2, suf_idx = 1, suf_pow = N - 2; 
             pref_idx >= 0; 
             --pref_idx, ++suf_idx, --suf_pow)
        {
            if (pref_hash == suf_hash)
            {
                if (compare(s, 0, pref_idx + 1, suf_idx))
                    return s.substr(0, pref_idx + 1);
            }

            // update prefix and suffix hashes
            pref_hash = ( pref_hash + modulo - (static_cast<data_t>(s[pref_idx]) - 'a') ) % modulo;
            assert(!(pref_hash % R)); // !!! This assertion fails. Can not devide !
            pref_hash = pref_hash / R; // reduse polynom power

            suf_hash = (suf_hash + modulo - (static_cast<data_t>(s[suf_idx]) - 'a') * R_powers[suf_pow] ) % modulo;
        }

        return {};
    }

    bool compare(const std::string& s, int beg1, int end1, int beg2)
    {
        while (beg1 < end1)
        {
            if (s[beg1] != s[beg2])
                return false;
            ++beg1;
            ++beg2;
        }

        return true;
    }
};
}

void LongestHappyPrefix()
{
    Solution sol;
    std::string s;
    std::string res;

    s = "level";
    res = sol.longestPrefix(s);
    assert(res == "l");
}