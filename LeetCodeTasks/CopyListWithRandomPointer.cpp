#include <unordered_map>
#include <iostream>

namespace
{
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head)
    {
        if (nullptr == head)
            return nullptr;

        std::unordered_map<unsigned int, int> pos2random_orig;
        std::unordered_map<int, Node*> pos2pointer_copy;
        auto res = copyWithoutRandom(head, pos2random_orig, pos2pointer_copy);

        print(pos2random_orig);
        print(pos2pointer_copy);

        addRandom(res, pos2random_orig, pos2pointer_copy);
        return res;
    }
private:
    Node* copyWithoutRandom(Node* const head, std::unordered_map<unsigned int, int>& pos2random_orig,
        std::unordered_map<int, Node*>& pos2pointer_copy)
    {
        std::unordered_map<Node*, int> pointer2pos_orig{ { nullptr, -1 } }; // local map
        pos2pointer_copy.insert({ -1, nullptr });

        // do copy
        unsigned int pos = 0;
        auto res = new Node(head->val);
        pos2pointer_copy.insert({ pos, res });
        pointer2pos_orig.insert({ head, pos });
        ++pos;

        auto curr = res;
        auto to_copy = head->next;
        while (to_copy)
        {
            auto copy = new Node(to_copy->val);
            curr->next = copy;

            pos2pointer_copy.insert({ pos, copy });
            pointer2pos_orig.insert({ to_copy, pos });
            ++pos;

            // move on
            curr = curr->next;
            to_copy = to_copy->next;
        }

        // fill pos2random_orig
        for (curr = head, pos = 0; curr != nullptr; curr = curr->next, ++pos)
        {
            const auto random_pos = pointer2pos_orig.find(curr->random)->second;
            pos2random_orig.insert({ pos, random_pos });
        }

        return res;
    }

    void addRandom(Node* res, const std::unordered_map<unsigned int, int>& pos2random_orig,
        const std::unordered_map<int, Node*>& pos2pointer_copy)
    {
        for (unsigned int pos = 0; res != nullptr; res = res->next, ++pos)
        {
            const auto random_pos = pos2random_orig.find(pos)->second;
            res->random = pos2pointer_copy.find(random_pos)->second;
        }
    }

    void print(const std::unordered_map<unsigned int, int>& pos2pos_orig)
    {
        for (const auto& p : pos2pos_orig)
        {
            std::cout << "Random at position " << p.first << " points to position " << p.second << "\n";
        }

        std::cout << "\n";
    }

    void print(const std::unordered_map<int, Node*>& pos2pointer_copy)
    {
        for (const auto& p : pos2pointer_copy)
        {
            if (p.first == -1)
            {
                std::cout << "Position " << p.first << " points to nullptr\n";
            }
            else
            {
                std::cout << "Position " << p.first << " contains " << p.second->val << " value\n";
            }
        }

        std::cout << "\n";
    }
};
}

void CopyListWithRandomPointer()
{
    auto seven = new Node(7);
    auto thirteen = new Node(13);
    auto eleven = new Node(11);
    auto ten = new Node(10);
    auto one = new Node(1);

    seven->next = thirteen;
    seven->random = nullptr;

    thirteen->next = eleven;
    thirteen->random = seven;

    eleven->next = ten;
    eleven->random = one;

    ten->next = one;
    ten->random = eleven;

    one->next = nullptr;
    one->random = seven;

    Solution sol;
    auto deep_copy = sol.copyRandomList(seven);
}