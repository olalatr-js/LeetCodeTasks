#include < vector>
#include <string>

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
        std::vector<std::string> binaryTreePaths(TreeNode* root)
        {
            m_res.clear();
            if (!root)
                return {};

            dfs(root, std::string());
            return m_res;
        }

        void dfs(TreeNode* root, std::string old_path)
        {
            old_path += std::to_string(root->val);
            if (!root->left && !root->right)
            {
                m_res.push_back(old_path);
                return;
            }

            if (root->left)
            {
                dfs(root->left, old_path + "->");
            }

            if (root->right)
            {
                dfs(root->right, old_path + "->");
            }
        }

        std::vector<std::string> m_res;
    };
}

void BinaryTreePaths()
{

}