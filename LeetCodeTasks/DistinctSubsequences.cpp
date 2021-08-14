#include <string>
#include <unordered_map>

namespace
{
class Solution 
{
public:
    int numDistinct(std::string s, std::string t)
    {
        const auto stat_s = calc_statistics(s);
        m_res = 0;
        //const auto N_t = static_cast<int>(t.size());
        //recursive(0, t);
        auto last_pos = -1;
        for (char ch : t)
        {
            const auto itr = stat_s.find(ch);
            if (itr == stat_s.end())
                return 0;

            for (auto pos : itr->second)
            {
                last_pos = pos;
                break;
            }
        }

        return m_res;
    }

private:
    int m_res;

    void recursive();

    static std::unordered_map<char, std::vector<int>> calc_statistics(const std::string& str)
    {

    }
};
}

void DistinctSubsequences()
{

}