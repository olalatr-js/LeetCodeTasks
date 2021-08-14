#include <climits>
#include <algorithm>
#include <queue>
#include <stdexcept>

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
    int minDepth(TreeNode* root)
    {
        //m_min_depth = INT_MAX;
        //recursive(root, 0);

        //return m_min_depth == INT_MAX ? 0 : m_min_depth;

        return BFS(root);
    }
private:
    int BFS(TreeNode* root)
    {
        if (!root)
            return 0;

        std::queue<std::pair<TreeNode*, int>> q;
        q.push(std::make_pair(root,1));
        while (!q.empty())
        {
            const auto curr = q.front().first;
            const auto depth = q.front().second;
            q.pop();

            if (nullptr == curr->left && nullptr == curr->right)
                return depth;
            if (curr->left)
                q.push(std::make_pair(curr->left, depth + 1));
            if (curr->right)
                q.push(std::make_pair(curr->right, depth + 1));
        }

        throw std::logic_error("Never gets here");
    }

    int m_min_depth;

    void recursive(TreeNode* root, int depth)
    {
        if (!root)
            return;

        ++depth;

        if (root->left == nullptr && root->right == nullptr)
        {
            m_min_depth = std::min(m_min_depth, depth);
        }

        recursive(root->left, depth);
        recursive(root->right, depth);
    }
};
}

void MinimumDepthOfBinaryTree()
{

}