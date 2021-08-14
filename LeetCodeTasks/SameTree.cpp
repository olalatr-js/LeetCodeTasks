#include "TreeNode.h"
#include <stack>

namespace
{
class Solution
{
public:
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if (p == nullptr && q == nullptr)
            return true;

        std::stack<TreeNode*> stk_p;
        std::stack<TreeNode*> stk_q;
        if (p)
            stk_p.push(p);
        if (q)
            stk_q.push(q);

        if (stk_p.size() != stk_q.size())
            return false;

        while (!stk_p.empty())
        {
            const auto curr_p = stk_p.top();
            stk_p.pop();
            const auto curr_q = stk_q.top();
            stk_q.pop();

            if (!compare(curr_p, curr_q))
                return false;

            // at this stage we know that curr_p and curr_q are structurally identical
            if (curr_p->left)
            {
                stk_p.push(curr_p->left);
                stk_q.push(curr_q->left);
            }

            if (curr_p->right)
            {
                stk_p.push(curr_p->right);
                stk_q.push(curr_q->right);
            }
        }

        return true;
    }

protected:
    bool compare(const TreeNode* lhs, const TreeNode* rhs)
    {
        if (lhs->val != rhs->val)
            return false;

        if (lhs->left && !rhs->left)
            return false;
        if (!lhs->left && rhs->left)
            return false;

        if (lhs->right && !rhs->right)
            return false;
        if (!lhs->right && rhs->right)
            return false;

        return true;
    }
};
}

void SameTree()
{
    // [10,5,15]
    // [10, 5, null, null, 15]
}