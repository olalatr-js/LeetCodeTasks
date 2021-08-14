#include <vector>
#include <string>
#include <unordered_map>
#include <set>

namespace
{
class Solution 
{
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words)
    {
        const auto SN = static_cast<int>(s.size());
        const auto WN = static_cast<int>(words.size());
        if (SN == 0 || WN == 0)
            return {};

        const auto step = static_cast<int>(words[0].size());
        std::unordered_map<std::string, int> banchmark_hist;

        std::unordered_map<int, std::string> tokens;
        /*
        std::vector<int> candidates;

        for (auto cand : candidates)
        {

        }
        */

        auto left = 0, right = 0;
        std::unordered_map<std::string, int> hist_to_compare;
        while (right < SN)
        {
            auto& word = tokens[right];
            ++hist_to_compare[word];
        }

        //for (; right < SN; ++right)
        //{

        //}
    }




















    std::vector<int> accepted_but_slow(std::string s, std::vector<std::string>& words) 
    {
        const auto N = static_cast<int>(s.size());
        const auto M = static_cast<int>(words.size());
        if (N == 0 || M == 0)
            return {};

        const auto step = static_cast<int>(words[0].size());
        const auto words_len = M * step;
        const auto last_possible_pos = N - words_len;
        if (last_possible_pos < 0)
            return {};

        std::unordered_map<std::string, int> benchmark_hist;
        std::unordered_map<int, std::string> index2word;
        std::set<int> candidates;

        for (auto& word : words)
        {
            ++benchmark_hist[word];
            size_t pos = 0;
            auto word_found = false;
            while ((pos = s.find(word, pos)) != std::string::npos)
            {
                word_found = true;
                const auto pos_int = static_cast<int>(pos);
                index2word.insert(std::make_pair(pos_int, word));
                if (pos_int <= last_possible_pos)
                {
                    candidates.insert(pos_int);
                }

                ++pos;
            }

            if (!word_found)
                return {};
        }
        const auto index2word_end = index2word.end();

        std::vector<int> res;
        for (auto cand : candidates)
        {
            std::unordered_map<std::string, int> hist_to_compare;
            auto hist_are_equal = true;
            for (auto word_pos = cand; word_pos < cand + words_len; word_pos += step)
            {
                const auto index2word_itr = index2word.find(word_pos);
                if (index2word_itr == index2word_end)
                {
                    hist_are_equal = false;
                    break;
                }

                const auto& word = index2word_itr->second;
                ++hist_to_compare[word];
                if (hist_to_compare[word] > benchmark_hist[word])
                {
                    hist_are_equal = false;
                    break;
                }
            }

            if (hist_are_equal)
                res.push_back(cand);
        }

        return res;
    }
};
}

/*

"barfoothefoobarman"
["foo","bar"]
"wordgoodgoodgoodbestword"
["word","good","best","word"]
"foofoobarfoothebarfootrash"
["bar", "foo", "the"]
"abababab"
["a", "b", "a"]
"aaa"
["a", "a"]
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
["a", "a", "a", "a", "a", "a", "a", "a",  "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a"]

*/

void SubstringWithConcatenationOfAllWords()
{
    Solution sol;

    std::string s("barfoothefoobarman");
    std::vector<std::string> words{ "foo","bar" };
    auto res = sol.findSubstring(s, words);

    s = "wordgoodgoodgoodbestword";
    words = { "word", "good", "best", "word" };
    res = sol.findSubstring(s, words);

    s = "foofoobarfoothebarfootrash";
    words = { "bar", "foo", "the" };
    res = sol.findSubstring(s, words);

    s = "abababab";
    words = { "a", "b", "a" };
    res = sol.findSubstring(s, words); // Expected [0,2,4]

    s = "aaa";
    words = { "a", "a" };
    res = sol.findSubstring(s, words);

    s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    words = { "a", "a", "a", "a", "a", "a", "a", "a",  "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a" };
    res = sol.findSubstring(s, words);
}