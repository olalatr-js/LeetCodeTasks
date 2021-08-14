#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>

namespace
{

// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node* cloneGraph(Node* node)
    {
        if (!node)
            return node;

        CopyOnlyVertices(node);
        AddEdges(node);
        return m_orig2copy.find(node)->second;
    }

private:
    void CopyOnlyVertices(Node* orig)
    {
        m_visited.clear();
        m_orig2copy.clear();
        DFS(orig);
    }

    void DFS(Node* orig)
    {
        auto copy = new Node(orig->val);
        m_orig2copy.insert({ orig, copy });
        m_visited.insert(orig);
        for (auto node_to_visit : orig->neighbors)
        {
            if (m_visited.end() == m_visited.find(node_to_visit))
            {
                DFS(node_to_visit);
            }
        }
    }

    void AddEdges(Node* orig)
    {
        m_visited.clear();
        std::queue<Node*> q;
        q.push(orig);
        while (!q.empty())
        {
            auto orig_node = q.front();
            q.pop();

            const auto copy_node = m_orig2copy.find(orig_node)->second;
            std::vector<Node*> copy_neighbors(orig_node->neighbors.size());
            std::transform(orig_node->neighbors.cbegin(), orig_node->neighbors.cend(), copy_neighbors.begin(),
                [this](Node* orig_n)
                {
                    return m_orig2copy.find(orig_n)->second;
                });
            copy_node->neighbors = std::move(copy_neighbors);

            m_visited.insert(orig_node);
            for (auto node_to_visit : orig_node->neighbors)
            {
                if (m_visited.find(node_to_visit) == m_visited.end())
                {
                    q.push(node_to_visit);
                }
            }
        }
    }

    std::unordered_set<Node*> m_visited;
    std::unordered_map<Node*, Node*> m_orig2copy;
};
}

void CloneGraph()
{
    auto one = new Node(1);
    auto two = new Node(2);
    auto three = new Node(3);
    auto four = new Node(4);

    one->neighbors = std::vector<Node*>{two, four};
    two->neighbors = std::vector<Node*>{one, three};
    three->neighbors = std::vector<Node*>{two, four};
    four->neighbors = std::vector<Node*>{one, three};

    Solution sol;
    auto res = sol.cloneGraph(one);
}