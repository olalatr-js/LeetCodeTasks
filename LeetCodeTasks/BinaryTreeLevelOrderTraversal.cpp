#include <vector>
#include <queue>

namespace
{
struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> res;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            const auto N = q.size();
            std::vector<int> row(N);
            for (auto i = 0u; i < N; ++i)
            {
                const auto curr = q.front();
                q.pop();

                row[i] = curr->val;
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }

            res.push_back(std::move(row));
        }

        return res;
    }
};
}

void BinaryTreeLevelOrderTraversal()
{

}