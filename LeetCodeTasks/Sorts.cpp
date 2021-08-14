#include <algorithm>
#include <vector>
#include <cassert>
#include <chrono>

template <typename T>
int partition_incorrect(T* a, int lo, int hi)
{
	const auto p_idx = (lo + hi) / 2;
	auto j = lo;
	for (auto i = lo; i <= hi; ++i)
	{
		if (a[i] < a[p_idx])
		{
			std::swap(a[i], a[j]);
			++j;
		}
	}

	return j;
}

// partition which takes a[lo] as a pivot element
// similar to std::remove but at the end does swap with the pivot element. So
// that pivot element is in proper position
template <typename T>
int partition_lo(T* a, int lo, int hi)
{
	// a[lo] is pivot element
	int j = lo;
	for (auto i = lo + 1; i <= hi; ++i)
	{
		if (a[i] < a[lo])
		{
			++j;
			std::swap(a[i], a[j]);
		}
	}

	std::swap(a[j], a[lo]);
	return j;
}

// correct like in Sedgewick
template <typename T>
int partition(T* a, int lo, int hi)
{
	auto i = lo + 1;
	auto j = hi;
	// a[lo] is pivot element
	while (true)
	{
		while (i <= hi && a[i] < a[lo])
			++i;

		while (lo + 1 <= j && a[lo] < a[j])
			--j;

		if (i >= j)
			break;

		std::swap(a[i], a[j]);
		++i;
		--j;
	}

	std::swap(a[lo], a[j]);
	return j;
}

template <typename T>
int partition3(T* a, int lo, int hi)
{
	// a[lo] is pivot value
	int i = lo;
	int j = hi + 1;

	while (true)
	{
		do
		{
			++i;
		} while (a[i] < a[lo] && i <= hi);

		do
		{
			--j;
		} while (a[lo] < a[j]);

		if (i >= j)
			break;

		std::swap(a[i], a[j]);
	}

	std::swap(a[lo], a[j]);
	return j;
}

template <typename T>
void my_qsort(T* a, int l, int r)
{
	if (l >= r)
		return;

	const auto pivot_idx = partition(a, l, r);
	my_qsort(a, l, pivot_idx - 1);
	my_qsort(a, pivot_idx + 1, r);
}

template <typename T>
void my_qsort(T* a, int N)
{
	my_qsort(a, 0, N - 1);
}

template <typename T>
void ins_sort(T* a, int N)
{
	for (auto i = 1; i < N; ++i)
	{
		if (a[i] < a[i - 1])
		{
			auto j = i;
			while (0 < j && a[j] < a[j - 1])
			{
				std::swap(a[j], a[j - 1]);
				--j;
			}
		}
	}
}

void test_ins_sort()
{
	std::vector<int> v_act;
	std::vector<int> v_exp;

	v_act = { 1,2,3,1,5,2 };
	v_exp = v_act;
	ins_sort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	v_act = { 1,2,3,4,5,6,7 };
	v_exp = v_act;
	ins_sort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	v_act = { 7,6,5,4,3,2,1 };
	v_exp = v_act;
	ins_sort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	v_act = { 2, 1 };
	v_exp = v_act;
	ins_sort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	v_act = {  1 };
	v_exp = v_act;
	ins_sort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	const auto N = 10000;
	const auto seed = time(nullptr);
	srand(seed);
	v_act.resize(N);
	for (auto i = 0; i < N; ++i)
	{
		v_act[i] = rand() % 120;
	}
	v_exp = v_act;

	ins_sort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);
}

void Sorts()
{
	test_ins_sort();

	std::vector<int> v_act;
	std::vector<int> v_exp;

	v_act = { 1,2,3,1,5,2 };
	v_exp = v_act;
	my_qsort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	v_act = {1,2,3,4,5,6,5,4,3,2,3,4,5,7,8,7,6,5,4,1,1,2,3,4,5,5};
	v_exp = v_act;
	my_qsort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	v_act = { 9,8,7,5,1,1,1,1,3,9,7,6,5,4,3,1,1,2,2,3,4,5,6,6,2,1,2 };
	v_exp = v_act;
	my_qsort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);

	const auto N = 10000;
	const auto seed = time(nullptr);
	srand(seed);
	v_act.resize(N);
	for (auto i = 0; i < N; ++i)
	{
		v_act[i] = rand() % 120;
	}
	v_exp = v_act;

	my_qsort(v_act.data(), v_act.size());
	std::sort(v_exp.begin(), v_exp.end());
	assert(v_exp == v_act);
}