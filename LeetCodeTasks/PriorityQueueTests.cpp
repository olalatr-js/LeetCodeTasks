#include "PriorityQueue.h"
#include <queue>
#include <random>
#include <chrono>
#include <cassert>

template<typename CompT>
void TheSimplestTest(const CompT& comp)
{
	PriorityQueue<double, decltype(comp)> my_pq(7, comp);
	my_pq.push(2.);
	my_pq.push(1.);
	my_pq.push(3.);
}

template<typename CompT>
void DoublesTest(const CompT& comp)
{
	constexpr int N = 12345;
	PriorityQueue<double, decltype(comp)> my_pq(N, comp);
	std::priority_queue<double, std::vector<double>, decltype(comp)> stl_pq(comp);

	std::vector<std::pair<double, std::string>> trace;

	const auto seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(-100.0, 100.0);
	for (auto i = 0; i < 10000; ++i)
	{
		const auto val = distribution(generator);
		if (val > 0.)
		{
			my_pq.push(val);
			stl_pq.push(val);
			trace.emplace_back(val, "push");
		}
		else
		{
			if (!my_pq.empty())
				my_pq.pop();
			if (!stl_pq.empty())
				stl_pq.pop();
			trace.emplace_back(val, "pop");
		}

		assert(my_pq.size() == stl_pq.size());
		if (!my_pq.empty() && !stl_pq.empty())
			assert(my_pq.top() == stl_pq.top());
	}

	auto kkk = 1;
}

template<typename CompT>
void IntTestRandom(const CompT& comp)
{
	constexpr int N = 12345;
	PriorityQueue<int, decltype(comp)> my_pq(N, comp);
	std::priority_queue<int, std::vector<int>, decltype(comp)> stl_pq(comp);

	std::vector<std::pair<int, std::string>> trace;

	const auto seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(-100, 100);
	for (auto i = 0; i < 10000; ++i)
	{
		const auto val = distribution(generator);
		if (val > 0)
		{
			my_pq.push(val);
			stl_pq.push(val);
			trace.emplace_back(val, "push");
		}
		else
		{
			if (!my_pq.empty())
				my_pq.pop();
			if (!stl_pq.empty())
				stl_pq.pop();
			trace.emplace_back(-1, "pop");
		}

		assert(my_pq.size() == stl_pq.size());
		if (!my_pq.empty() && !stl_pq.empty())
			assert(my_pq.top() == stl_pq.top());
	}

	auto kkk = 1;
}

template<typename CompT>
void IntTestSimple(const CompT& comp)
{
	constexpr int N = 12345;
	PriorityQueue<int, decltype(comp)> my_pq(N, comp);
	std::priority_queue<int, std::vector<int>, decltype(comp)> stl_pq(comp);

	std::vector<std::pair<int, bool>> task{ 
		{1,true},   {2,true},   {3,true},   {4,true},   {5,true},   {6,true},   {7,true},    {8,true},   {9,true},   {10,true},
		{-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false},  {-1,false}, {-1,false}, {-1,false},
		{9,true},   {10,true},  {11,true},  {10,true},  {9,true},   {8,true},   {7,true},    {6,true},   {5,true},   {4,true},
		{-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false},  {-1,false}, {-1,false}, {-1,false},
		{3,true},   {2,true},   {1,true},   {0,true},   {5,true},   {6,true},   {7,true},    {8,true},   {7,true},   {8,true},
		{-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false},  {-1,false}, {-1,false}, {-1,false},
		{1,true}, {2,true}, {3,true}, {4,false}, {5,true}, {6,true}, {7,true}, {8,true}, {7,true}, {8,true},
	    {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false}, {-1,false},  {-1,false} };

	for (size_t i = 0; i < task.size(); ++i)
	{
		if (task[i].second)
		{
			my_pq.push(task[i].first);
			stl_pq.push(task[i].first);
		}
		else
		{
			if (!my_pq.empty())
				my_pq.pop();
			if (!stl_pq.empty())
				stl_pq.pop();
		}

		assert(my_pq.size() == stl_pq.size());
		if (!my_pq.empty() && !stl_pq.empty())
			assert(my_pq.top() == stl_pq.top());
	}
}

void PriorityQueueTests()
{
	TheSimplestTest(std::less<double>());
	IntTestSimple(std::less<int>());
	IntTestRandom(std::less<int>());
	DoublesTest(std::less<double>());


	TheSimplestTest(std::greater<double>());
	IntTestSimple(std::greater<int>());
	IntTestRandom(std::greater<int>());
	DoublesTest(std::greater<double>());
}