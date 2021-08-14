#include "TreeNode.h"

#include <vector>
#include <unordered_map>

namespace
{
class Solution
{
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
    {
        m_val2idx.clear();
        const auto N = static_cast<int>(inorder.size());
        for (auto i = 0; i < N; ++i)
        {
            m_val2idx[inorder[i]] = i;
        }

        m_root_p_idx = -1;
        return recursive(preorder, inorder, 0, N - 1);
    }

private:
    TreeNode* recursive(const std::vector<int>& preorder, const std::vector<int>& inorder,
        int beg, int end)
    {
        if (beg > end)
            return nullptr;

        ++m_root_p_idx;
        const auto root_val = preorder[m_root_p_idx];
        auto res = new TreeNode(root_val);
        const auto root_i_idx = m_val2idx.at(root_val);
        res->left = recursive(preorder, inorder, beg, root_i_idx - 1);
        res->right = recursive(preorder, inorder, root_i_idx + 1, end);
        return res;
    }

    std::unordered_map<int, int> m_val2idx;
    int m_root_p_idx;
};
}

void ConstructBinaryTreeFromPreorderAndInorderTraversal()
{

}