namespace
{
	//Definition for singly-linked list.
	struct ListNode 
	{
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	/**
	 * Definition for singly-linked list.
	 * struct ListNode {
	 *     int val;
	 *     ListNode *next;
	 *     ListNode(int x) : val(x), next(NULL) {}
	 * };
	 */
	class Solution
	{
	public:
		ListNode* reverseKGroup(ListNode* head, int k)
		{
			ListNode* curr = head;
			ListNode* res = nullptr;
			ListNode* before_reverse_head = nullptr;
			while (curr)
			{
				ListNode* prev = nullptr;
				ListNode* next;
				ListNode* before_reverse_head_local = curr;
				auto i = 0;
				for (; i < k; ++i)
				{
					if (!curr)
						break;
					next = curr->next;
					curr->next = prev;

					// move on
					prev = curr;
					curr = next;
				}

				if (i != k)
				{
					prev = reverse(prev);
				}

				if (!res)
					res = prev;

				if (before_reverse_head)
				{
					before_reverse_head->next = prev;
				}

				before_reverse_head = before_reverse_head_local;
			}

			return res;
		}
	private:
		ListNode* reverse(ListNode* head)
		{
			ListNode* curr = head;
			ListNode* prev = nullptr;
			ListNode* next;
			while (curr)
			{
				next = curr->next;
				curr->next = prev;

				// move on
				prev = curr;
				curr = next;
			}

			return prev;
		}
	};

	ListNode* prepare_input(int N)
	{
		auto head = new ListNode(1);
		auto curr = head;
		for (auto i = 2; i <= N; ++i)
		{
			auto node = new ListNode(i);
			curr->next = node;
			curr = node;
		}

		return head;
	}
}

void ReverseNodesInKGroup()
{
	Solution s;

	auto input = prepare_input(5);
	auto output = s.reverseKGroup(input, 2);
}