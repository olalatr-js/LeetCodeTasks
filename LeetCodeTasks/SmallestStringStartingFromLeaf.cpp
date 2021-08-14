#include "TreeNode.h"
#include <string>
#include <algorithm>

namespace
{
class Solution
{
public:
    std::string smallestFromLeaf(TreeNode* root)
    {
        m_res.clear();
        if (!root)
            return {};
        dfs(root, std::string());
        std::reverse(m_res.begin(), m_res.end());
        return m_res;
    }
private:
    bool less_rev(const std::string& lhs, const std::string& rhs)
    {
        if (rhs.empty())
            return true;

        // now both lhs and rhs are not empty
        auto lhs_ritr = lhs.rbegin();
        auto rhs_ritr = rhs.rbegin();
        while (lhs_ritr != lhs.rend() && rhs_ritr != rhs.rend())
        {
            if (*lhs_ritr != *rhs_ritr)
                break;

            ++lhs_ritr;
            ++rhs_ritr;
        }

        if (lhs_ritr != lhs.rend() && rhs_ritr != rhs.rend())
            return *lhs_ritr < *rhs_ritr;

        if (lhs_ritr == lhs.rend() && rhs_ritr == rhs.rend())
            return false;

        if (lhs_ritr != lhs.rend())
            return false;

        return true;
    }

    void dfs(TreeNode* curr, std::string candidate)
    {
        candidate.push_back(static_cast<char>(curr->val + 'a'));
        if (!curr->left && !curr->right)
        {
#ifdef DBG
            std::cout << "Comparing " << candidate.c_str() << " and " << m_res.c_str() << "\n";
#endif
            if (less_rev(candidate, m_res))
            {
                m_res = candidate;
            }

#ifdef DBG
            std::cout << "Result  = " << m_res.c_str() << "\n" << "\n";
#endif
        }

        if (curr->left)
            dfs(curr->left, candidate);
        if (curr->right)
            dfs(curr->right, candidate);
    }

    std::string m_res;
};
}

/*
Test cases
[0,1,2,3,4,3,4]
[25,1,3,1,3,0,2]
[2,2,1,null,1,0,null,0]
[4,0,1,1]
*/
void SmallestStringStartingFromLeaf()
{

}