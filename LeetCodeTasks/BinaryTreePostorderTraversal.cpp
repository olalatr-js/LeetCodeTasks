#include <vector>
#include <stack>
#include <algorithm>

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

class Solution {
public:
    std::vector<int> postorderTraversal(TreeNode* root)
    {
        //std::vector<int> res;
        //recursive(root, res);
        //return res;

        //return IterativeWith1Stack(root);
        //return IterativeWith2Stack(root);
        return IterativeWith1Stack_Reverse(root);
    }
private:
    std::vector<int> IterativeWith1Stack_Reverse(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> res;
        std::stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty())
        {
            const auto curr = stk.top();
            stk.pop();
            res.push_back(curr->val);

            if (curr->left)
            {
                stk.push(curr->left);
            }

            if (curr->right)
            {
                stk.push(curr->right);
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }

    std::vector<int> IterativeWith2Stack(TreeNode* root)
    {
        if (!root)
            return {};

        std::stack<TreeNode*> st_temp;
        std::stack<TreeNode*> st_res;
        st_temp.push(root);
        while (!st_temp.empty())
        {
            const auto curr = st_temp.top();
            st_temp.pop();
            st_res.push(curr);

            if (curr->left)
            {
                st_temp.push(curr->left);
            }

            if (curr->right)
            {
                st_temp.push(curr->right);
            }
        }

        std::vector<int> res;
        while (!st_res.empty())
        {
            res.push_back(st_res.top()->val);
            st_res.pop();
        }

        return res;
    }

    std::vector<int> IterativeWith1Stack(TreeNode* root)
    {
        std::vector<int> res;
        std::stack<TreeNode*> st;
        auto curr = root;

        while (curr || !st.empty())
        {
            while (curr)
            {
                if (curr->right)
                {
                    st.push(curr->right);
                }
                st.push(curr);
                curr = curr->left;
            }

            curr = st.top();
            st.pop();

            if (curr->right && !st.empty() && curr->right == st.top())
            {
                st.pop();
                st.push(curr);
                curr = curr->right;
            }
            else
            {
                res.push_back(curr->val);
                curr = nullptr;
            }
        }

        return res;
    }

    void recursive(TreeNode* root, std::vector<int>& res)
    {
        if (!root)
        {
            return;
        }

        recursive(root->left, res);
        recursive(root->right, res);
        res.push_back(root->val);
    }
};
}

void BinaryTreePostorderTraversal()
{
    // case 1
    //       \
    //        2
    //       /
    //      3

    auto three = new TreeNode(3);
    auto two = new TreeNode(2, three, nullptr);
    auto one = new TreeNode(1, nullptr, two);

    Solution sol;
    auto res = sol.postorderTraversal(one);
}