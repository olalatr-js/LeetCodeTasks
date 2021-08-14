#include <iostream>
#include <vector>

namespace
{
	struct Int
	{
		Int() { std::cout << 1; }
		Int(int) { std::cout << 2; }
		~Int() { std::cout << 3; }
	};

	struct NC
	{
		NC() { std::cout << "a"; }
		NC(const NC&) = delete;
		NC& operator = (const NC&) = delete;

		NC(NC&&) { std::cout << "b"; }
		NC& operator = (NC&&) { std::cout << "c"; }
	};

	/*
	int f2()
	{
		int x = 0;
		const int* a = &x;
		int* const b = &x;

		*a = 1;
		*b = 1;

		int const y = 0;
		a = &y;
		b = &y;
	}
	*/

	void foo(int) {}
	void foo(float) {}
	void foo(int, int i =0) {}

	void boo()
	{
		//foo(1);
		foo(1.0f);
		foo(1,2);
	}

	template <int I, typename T>
	struct X {
		static const int s = 1;
	};

	template<int I>
	struct X<I, int>
	{
		static const int s = 2;
	};

	void templ()
	{
		X<0, int> x;
		std::cout << x.s;
		std::cout << "\n";
	}

	struct B
	{
		explicit B(int) {}
	};

	void q11()
	{
		//B b1 = 1;
		B b2(2);
		B b3 = (B)1;
	}

	class Base
	{
	protected:
		int i;
	public:
		Base() :i(0) {}
		virtual ~Base() { i = 1; }
	};

	class Derr : public Base
	{
	public:
		Derr() : Base() {}
		virtual ~Derr() { std::cout << i; }
	};

	void q15()
	{
		Derr d;
	}
}

#define MAX 10+2

void Stryker()
{
	q15();
	std::cout << "\n" << "\n";

	templ();

	std::vector<NC> v;
	v.reserve(3);

	NC nc;
	v.push_back(NC{});
	v.emplace_back();
	v.push_back(std::move(nc));

	{
	std::cout << "\n";
	char a[] = "";
	auto sa = sizeof(a);
	std::cout << sa << "\n";
    }

	int a = 8;
	double b = 2.1715;
	int c = a - b;

	float x = 2.1;
	auto val = x++;

	int i = MAX * MAX;

	{
		Int ii;
		i = 10;
	}

}