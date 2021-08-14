#pragma once
#include <vector>
#include <stdexcept>

template <typename T, typename CompT = std::less<T>>
class PriorityQueue
{
public:
	PriorityQueue(int n) : m_capacity(n), m_heap(n)
	{}

	PriorityQueue(int n, const CompT& comp): m_capacity(n), m_heap(n), m_comp(comp)
	{}

	const T& top() const
	{
		return m_heap[0];
	}

	void pop()
	{
		if (m_size <= 0)
			throw std::logic_error("Failed to pop from empty PriorityQueue");
		std::swap(m_heap[0], m_heap[m_size - 1]);
		--m_size;
		sink(0);
	}

	void push(T val)
	{
		if (m_size >= m_capacity)
			throw std::logic_error("Failed to push because PriorityQueue reached its capacity");
		m_heap[m_size] = val;		
		swim(m_size);
		++m_size;
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
		//while (i > 0 && (m_heap[(i - 1) / 2] < m_heap[i]))
		while (i > 0 && m_comp(m_heap[(i - 1) / 2], m_heap[i]))
		{
			std::swap(m_heap[i], m_heap[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	void sink(int i)
	{
		auto child_i = 2 * i + 1;
		while (child_i < m_size)
		{
			//                            (m_heap[child_i] < m_heap[child_i + 1])
			if ((child_i + 1 < m_size) && m_comp(m_heap[child_i], m_heap[child_i + 1]))
				++child_i;
			// if (m_heap[i] >= m_heap[child_i])
			if (!m_comp(m_heap[i],m_heap[child_i]))
				break;
			std::swap(m_heap[i], m_heap[child_i]);
			i = child_i;
			child_i = 2 * i + 1;
		}
	}

	int m_size = 0;
	int m_capacity;
	std::vector<T> m_heap; // 0 based start index implementation
	CompT m_comp{};
};