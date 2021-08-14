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
    int maxDepth(TreeNode* root)
    {
        std::stack<std::pair<TreeNode*, int>> stk;
        auto curr = root;
        auto max_depth = 0;
        auto curr_depth = 0;
        while (curr || !stk.empty())
        {
            while (curr)
            {
                stk.push(std::make_pair(curr, ++curr_depth));
                curr = curr->left;
            }

            const auto p = stk.top();
            curr = p.first;
            curr_depth = p.second;

            //std::cout << "Val = " << curr->val << ", depth = " << curr_depth 
            //    << ", stack size = " << stk.size() << std::endl;

            if (curr_depth > max_depth)
            {
                max_depth = curr_depth;
            }

            --curr_depth;
            stk.pop();

            curr = curr->right;
            ++curr_depth;
        }

        return max_depth;
    }
};
}

void MaximumDepthOfBinaryTree()
{

}