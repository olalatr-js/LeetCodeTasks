#include <vector>
#include <unordered_map>
#include <algorithm>

namespace
{
class Solution
{
public:
    int maximumUniqueSubarray(std::vector<int>& nums)
    {
        const auto N = static_cast<int>(nums.size());
        auto beg = 0;
        auto max_score = 0;
        std::unordered_map<int, int> last_seen; // number to position
        std::vector<int> acc(N);
        acc[0] = nums[0];
        for (auto i = 1; i < N; ++i)
        {
            acc[i] = nums[i] + acc[i - 1];
        }

        for (auto end = 0; end < N; ++end)
        {
            if (last_seen.count(nums[end]))
            {
                beg = std::max(beg, last_seen[nums[end]] + 1);
            }

            last_seen[nums[end]] = end;

            max_score = std::max(max_score, acc[end] - acc[beg] + nums[beg]);
        }

        return max_score;
    }
};
}

void MaximumErasureValue()
{

}