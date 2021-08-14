#include <tuple>

namespace
{
class Node
{
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
    
class Solution
{
public:
    Node* flatten(Node* head)
    {
        if (!head)
            return head;

        return std::get<0>(recursive(head));
    }

private:
    std::tuple<Node*, Node*> recursive(Node* head)
    {
        auto curr = head;
        auto tail = head;
        while (curr)
        {
            tail = curr;
            if (curr->child)
            {
                Node* child_head;
                Node* child_tail;
                std::tie(child_head, child_tail) = recursive(curr->child);

                auto nxt = curr->next;
                curr->next = child_head;
                child_head->prev = curr;

                child_tail->next = nxt;
                if (nxt)
                {
                    nxt->prev = child_tail;
                }
            }

            curr = curr->next;
        }

        return { head, tail };
    }
};
}

void FlattenAMultilevelDoublyLinkedList()
{
    Solution sol;

    // Example 2
    // 1-- - 2-- - NULL
    // |
    // 3-- - NULL

    Node one{ 1, nullptr, nullptr, nullptr };
    Node two{ 2, nullptr, nullptr, nullptr };
    Node three{ 3, nullptr, nullptr, nullptr };

    one.next = &two;
    one.child = &three;
    two.prev = &one;

    const auto res = sol.flatten(&one);
}