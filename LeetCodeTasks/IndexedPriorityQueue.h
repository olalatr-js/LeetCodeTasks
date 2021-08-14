#pragma once
#include <vector>
#include <stdexcept>

template <typename T, typename CompT = std::less<T>>
class IndexedPriorityQueue
{
public:
	IndexedPriorityQueue(int n) : pq(n), qp(n, undeffined), keys(n)
	{}

	IndexedPriorityQueue(int n, const CompT& comp) : IndexedPriorityQueue(n)
	{
		m_comp = comp;
	}

	const T& top_key() const
	{
		return keys[pq[0]];
	}

	int top_index() const
	{
		return pq[0];
	}

	bool contains(int idx)
	{
		return qp[idx] != undeffined;
	}

	void pop()
	{
		if (m_size <= 0)
			throw std::logic_error("Failed to pop from empty IndexedPriorityQueue");
		const auto idx_to_delete = pq[0];
		exch(0, m_size - 1);
		--m_size;
		sink(0);
		qp[idx_to_delete] = undeffined;
	}

	void push(int idx, T val)
	{
		if (m_size >= static_cast<int>(keys.size()))
			throw std::logic_error("Failed to push because IndexedPriorityQueue reached its capacity");
		if (idx >= static_cast<int>(keys.size()))
			throw std::invalid_argument("Index is out of IndexedPriorityQueue bounds");
		if (qp[idx] != undeffined)
			throw std::invalid_argument("Index already present in IndexedPriorityQueue");

		pq[m_size] = idx;
		qp[idx] = m_size;
		keys[idx] = val;

		swim(m_size);
		++m_size;
	}

	void change_key(int idx, T new_key)
	{
		if (qp[idx] == undeffined)
			throw std::invalid_argument("Trying to change key for not-existing index");
		const auto heap_pos = qp[idx];
		keys[idx] = new_key;
		if ((heap_pos > 0) && m_comp(keys[pq[(heap_pos - 1) / 2]], keys[pq[heap_pos]]))
			swim(heap_pos);
		else
			sink(heap_pos);

	}

	bool empty() const
	{
		return m_size == 0;
	}

	int size() const
	{
		return m_size;
	}

private:
	void swim(int i)
	{
		// for std::less       m_heap[(i - 1) / 2] < m_heap[i]
		while (i > 0 && m_comp(keys[pq[(i - 1) / 2]], keys[pq[i]]))
		{
			exch(i, (i - 1) / 2);
			i = (i - 1) / 2;
		}
	}

	void sink(int i)
	{
		auto child_i = 2 * i + 1;
		while (child_i < m_size)
		{
			//  for std::less                    m_heap[child_i] < m_heap[child_i + 1]
			if ((child_i + 1 < m_size) && m_comp(keys[pq[child_i]], keys[pq[child_i + 1]]))
				++child_i;
			// foe std::less (m_heap[i] >= m_heap[child_i])
			if (!m_comp(keys[pq[i]], keys[pq[child_i]]))
				break;
			exch(i, child_i);
			i = child_i;
			child_i = 2 * i + 1;
		}
	}

	void exch(int i, int j)
	{
		std::swap(pq[i], pq[j]);
		qp[pq[i]] = i;
		qp[pq[j]] = j;
	}

	const int undeffined = -1;
	int m_size = 0;
	std::vector<int> pq; // heap with 0 based start index
	std::vector<int> qp; // index to heap position. qp[index] = heap position
	std::vector<T> keys;
	CompT m_comp{};
};