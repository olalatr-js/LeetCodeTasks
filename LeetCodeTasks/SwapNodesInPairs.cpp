namespace
{

	//Definition for singly-linked list.
	struct ListNode
	{
		int val;
		ListNode* next;
		ListNode(int x) : val(x), next(nullptr) {}
	};

class Solution
{
public:
	ListNode* swapPairs(ListNode* head)
	{
		auto res = head;
		ListNode* first = head;
		ListNode* second;
		// second node after swap on the previous cycle
		ListNode* prev_second = nullptr;
		while (true)
		{
			if (!first)
				return res;

			second = first->next;
			if (!second)
				return res;

			auto third = second->next;
			// do swap
			first->next = third;
			second->next = first;

			if (prev_second)
			{
				prev_second->next = second;
			}
			else
			{
				res = second;
			}

			prev_second = first;

			// move forward
			first = third;
		}
	}
};
}

void SwapNodesInPairs()
{
	Solution s;
	auto head = new ListNode(1);
	auto n2 = new ListNode(2);
	head->next = n2;
	auto n3 = new ListNode(3);
	n2->next = n3;
	auto n4 = new ListNode(4);
	n3->next = n4;

	auto output = s.swapPairs(head);
}