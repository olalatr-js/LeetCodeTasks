#include <vector>
#include <algorithm>

namespace
{
class Solution
{
public:
    std::vector<std::vector<int>> intervalIntersection(std::vector<std::vector<int>>& firstList, std::vector<std::vector<int>>& secondList)
    {
        const auto N1 = static_cast<int>(firstList.size());
        const auto N2 = static_cast<int>(secondList.size());
        if (N1 == 0 || N2 == 0)
            return {};

        auto i1 = 0;
        auto i2 = 0;
        std::vector<std::vector<int>> res;
        while (i1 < N1 && i2 < N2)
        {
            const auto& inter1 = firstList[i1];
            const auto& inter2 = secondList[i2];
            // | inter1|   | inter2|
            if (inter1[1] < inter2[0])
            {
                ++i1;
            }
            else if (inter2[1] < inter1[0]) // | inter2|   |inter1|
            {
                ++i2;
            }
            else  // intervals overlap
            {
                std::vector<int> overlap(2);
                overlap[0] = std::max(inter1[0], inter2[0]);
                overlap[1] = std::min(inter1[1], inter2[1]);
                res.push_back(overlap);

                if (inter1[1] == inter2[1])
                {
                    ++i1;
                    ++i2;
                }
                else if (inter1[1] < inter2[1]) // {  inter1    [inter2 }     ]
                {
                    ++i1;
                }
                else // [ inter2 {inter 1 ]   }
                {
                    ++i2;
                }
            }
        }

        return res;
    }
};
}

void IntervalListIntersections()
{
    // input
    // [[14,16]]
    // [[7, 13], [16, 20]]
    // expected output
    // [[16,16]]
}