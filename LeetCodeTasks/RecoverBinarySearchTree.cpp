#include "TreeNode.h"

#include <vector>
#include <algorithm>

namespace
{
class Solution 
{
public:
    void recoverTree(TreeNode* root)
    {
        m_prev = m_first = m_middle = m_last = nullptr;
        recursive(root);

        if (m_first && m_last)
        {
            std::swap(m_first->val, m_last->val);
        }
        else if (m_first && m_middle)
        {
            std::swap(m_first->val, m_middle->val);
        }
    }

private:
    void recursive(TreeNode* root)
    {
        if (!root)
            return;

        recursive(root->left);

        if (m_prev && m_prev->val > root->val)
        {
            if (m_first == nullptr && m_middle == nullptr)
            {
                m_first = m_prev;
                m_middle = root;
            }
            else
            {
                m_last = root;
            }
        }
        m_prev = root;

        recursive(root->right);
    }

    void recoverTree_ON_space(TreeNode* root) 
    {
        m_in_order_trav.clear();
        if (!root)
            return;

        recursive_in_order(root);
        std::sort(m_in_order_trav.begin(), m_in_order_trav.end());
        m_idx = 0;
        recursive_in_order_set(root);
    }

    void recursive_in_order(TreeNode* root)
    {
        if (!root)
            return;

        recursive_in_order(root->left);
        m_in_order_trav.push_back(root->val);
        recursive_in_order(root->right);
    }

    void recursive_in_order_set(TreeNode* root)
    {
        if (!root)
            return;

        recursive_in_order_set(root->left);
        root->val = m_in_order_trav[m_idx];
        ++m_idx;
        recursive_in_order_set(root->right);
    }

    std::vector<int> m_in_order_trav;
    int m_idx;

    TreeNode* m_prev;
    TreeNode* m_first;
    TreeNode* m_middle;
    TreeNode* m_last;
};
}

void RecoverBinarySearchTree()
{

}