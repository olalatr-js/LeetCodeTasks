#include "TreeNode.h"

#include <deque>
#include <stack>

namespace
{
class Solution {
public:
    bool isSymmetric(TreeNode* root)
    {
        std::deque<int> left_trav;
        std::stack<TreeNode*> stk;
        // First do left inorder traversal
        //if (root)
        //    stk.push_back(root);

        auto curr = root;
        while (curr || !stk.empty())
        {
            while (curr)
            {
                stk.push(curr);
                curr = curr->left;
            }

            curr = stk.top();
            stk.pop();
            left_trav.push_back(curr->val);

            curr = curr->right;
        }

        // Second do right inorder traversal.
        curr = root;
        while (curr || !stk.empty())
        {
            while (curr)
            {
                stk.push(curr);
                curr = curr->right;
            }

            curr = stk.top();
            stk.pop();

            if (curr->val != left_trav.front())
                return false;

            left_trav.pop_front();

            curr = curr->left;
        }

        return true;
    }
};
}

void SymmetricTree()
{

}