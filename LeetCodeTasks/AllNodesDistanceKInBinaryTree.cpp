#include "TreeNode.h"

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

namespace
{
//#define DEBUG_INFO

class Solution
{
public:
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int K)
    {
        auto to_parent = build_to_parent(root);

#ifdef DEBUG_INFO2
        print(to_parent);
#endif

        // Do BFS
        std::queue<TreeNode*> q;
        std::unordered_set<TreeNode*> visited;
        q.push(target);

        auto dist = 0;
        std::vector<int> res;
        while (!q.empty())
        {
            const auto N = q.size();
            for (size_t i = 0; i < N; ++i)
            {
                const auto node = q.front();
                q.pop();
                visited.insert(node);

#ifdef DEBUG_INFO
                std::cout << node->val << ", ";
#endif

                const auto parent = to_parent[node];
                if (parent && (visited.find(parent) == visited.end()))
                    q.push(parent);
                if (node->left && (visited.find(node->left) == visited.end()))
                    q.push(node->left);
                if (node->right && (visited.find(node->right) == visited.end()))
                    q.push(node->right);

                if (dist == K)
                {
                    res.push_back(node->val);
                }
            }

#ifdef DEBUG_INFO
            std::cout << "\n";
#endif

            if (dist == K)
                return res;
            ++dist;
        }

        return res;
    }

private:
    std::unordered_map<TreeNode*, TreeNode*> build_to_parent(TreeNode* root)
    {
        std::unordered_map<TreeNode*, TreeNode*> res;
        std::stack<TreeNode*> stk;
        if (root)
        {
            res[root] = nullptr;
            stk.push(root);
        }

        while (!stk.empty())
        {
            const auto parent = stk.top();
            stk.pop();

            if (parent->left)
            {
                res[parent->left] = parent;
                stk.push(parent->left);
            }

            if (parent->right)
            {
                res[parent->right] = parent;
                stk.push(parent->right);
            }
        }

        return res;
    }

    void print(const std::unordered_map<TreeNode*, TreeNode*>& to_parent)
    {
        for (const auto& edge : to_parent)
        {
            std::cout << edge.first->val << " -> ";
            if (edge.second)
            {
                std::cout << edge.second->val;
            }
            else
            {
                std::cout << "null";
            }

            std::cout << "\n";
        }
    }
};
}

void AllNodesDistanceKInBinaryTree()
{

}