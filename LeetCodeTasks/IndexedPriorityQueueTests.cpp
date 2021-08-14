#include "IndexedPriorityQueue.h"
#include <cassert>

void IndexedPriorityQueueTests()
{
	const auto N = 20;
	IndexedPriorityQueue<int> ipq(N);

	ipq.push(1, 10);
	ipq.push(3, 30);
	ipq.push(2, 20);
	ipq.push(4, 40);

	assert(ipq.top_index() == 4 && ipq.top_key() == 40);

	ipq.change_key(3, 3);
	ipq.pop();

	assert(ipq.top_index() == 2 && ipq.top_key() == 20);

	ipq.pop();

	assert(ipq.top_index() == 1 && ipq.top_key() == 10);
}