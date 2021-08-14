#include <unordered_set>

namespace
{
	struct my_hash
	{
		unsigned operator()(const std::pair<int, int>& p) const
		{
			return 3000 * p.first + p.second;
		}
	};
}

void PickNik()
{
	auto q5 = (0x16 == 16);
	auto q5_1 = 0x16;

	auto q7 = (2 << 3);

	std::unordered_set<std::pair<int, int>, my_hash> us;
}