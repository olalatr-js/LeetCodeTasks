#include "TreeNode.h"
#include <vector>

namespace
{
class Solution
{
public:
    std::vector<TreeNode*> generateTrees(int n)
    {
        if (n < 1)
            return { nullptr };

        return recursive(1, n);
    }

private:
    std::vector<TreeNode*> recursive(int low, int hi)
    {
        if (low > hi)
            return { nullptr };

        if (low == hi)
            return { new TreeNode(low) };

        std::vector<TreeNode*> res;
        for (auto i = low; i <= hi; ++i)
        {
            const auto left_sub_trees = recursive(low, i - 1);
            const auto right_sub_trees = recursive(i + 1, hi);
            for (const auto l_root : left_sub_trees)
            {
                for (const auto r_root : right_sub_trees)
                {
                    auto bst_root = new TreeNode(i, l_root, r_root);
                    res.push_back(bst_root);
                }
            }
        }

        return res;
    }
};
}

void UniqueBinarySearchTreesII()
{

}