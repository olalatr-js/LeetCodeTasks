#include <algorithm>

namespace
{
class Solution
{
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {
        int w = 0;
        if (ax1 < bx1)
        {
            if (bx1 >= ax2)
                return 0;
            else
                w = std::min(ax2, bx2) - bx1;
        }
        else // ax1 >= bx1
        {
            if (bx2 <= ax1)
                return 0;
            else
                w = std::min(ax2, bx2) - ax1;
        }

        int h = 0;
        if (ay1 < by1)
        {
            if (by1 >= ay2)
                return 0;
            else
                h = std::min(ay2, by2) - by1;
        }
        else // ay1 >= by1
        {
            if (by2 <= ay1)
                return 0;
            else
                h = std::min(ay2, by2) - ay1;
        }

        return w * h;
    }
};
}

void RectangleArea()
{
    Solution sol;
    int s;

    s = sol.computeArea(-3, 0, 
                         3, 4,
        
                         0, -1,
                         9,  2);
}