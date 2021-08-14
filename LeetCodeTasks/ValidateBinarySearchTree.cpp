#include <climits>
#include <stack>

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
    bool isValidBST(TreeNode* root)
    {
        return iterative_inorder(root);
        /* recursive approach does NOT pass when nodes have INT_MAX, INT_MIN values
        if (root && root->val == INT_MAX && !root->left && !root->right)
            return true;

        if (root && root->val == INT_MIN && !root->left && !root->right)
            return true;

        return recursive(root, INT_MIN, INT_MAX);
        */
    }

private:
    bool iterative_inorder(TreeNode* root)
    {
        auto curr = root;
        std::stack<TreeNode*> stk;
        int* prev_val = nullptr;
        while (curr || !stk.empty())
        {
            while (curr)
            {
                stk.push(curr);
                curr = curr->left;
            }

            curr = stk.top();
            stk.pop();

            if (prev_val && *prev_val >= curr->val)
                return false;

            prev_val = &(curr->val);
            curr = curr->right;
        }

        return true;
    }

    bool recursive(TreeNode* root, int low_thr, int hi_thr)
    {
        if (!root)
            return true;

        const auto val = root->val;

        if (val == INT_MAX)
        {
            if (hi_thr != INT_MAX)
                return false;
        }
        else if (val == INT_MIN)
        {
            if (low_thr != INT_MIN)
                return false;
        }
        else if (root->val <= low_thr || hi_thr <= root->val)
            return false; // root->val must be inside (low_thr, hi_thr)

        return recursive(root->left, low_thr, root->val) && recursive(root->right, root->val, hi_thr);
    }
};
}

void ValidateBinarySearchTree()
{
    // wrong answer for [2147483647]. Expected true
}