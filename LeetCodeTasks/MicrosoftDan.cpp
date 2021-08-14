#include <unordered_map>
#include <stdexcept>

template <typename KeyT, typename ValT>
class hash_table
{
public:
	hash_table(int N): m_cont(N)
	{}

	void put(KeyT k, ValT v)
	{
		const auto h = m_hasher(k); //std::hash(k);
		h = h % m_cont.size();
		const auto& lst = m_cont[h];
		for (const auto& p : lst)
		{
			if (p.first == k)
			{
				p.second = v;
				return;
			}
		}

		// not found in the list
		lst.insert({k, v});
	}

	ValT& get(KeyT k)
	{
		auto h = m_hasher(k); // std::hash(k);
		h = h % m_cont.size();
		auto& lst = m_cont[h];
		for (auto& p : lst)
		{
			if (p.first == k)
				return p.second;
		}

		throw std::invalid_argument("Not found");

		/*
		// C++ style
		static ValT def{}; // default
		lst.insert({k, def});

		return lst.back().second;
		*/
	}

private:
	std::vector < std::list< std::pair<KeyT, ValT > > > m_cont;
	std::hash<KeyT> m_hasher;
};

// {1, 's'}, {1, 't'}
// rewrite
// do nothing return false
// throw exception

void MicrosoftDan()
{
	hash_table<int, char> table(8);
	table.get(3) = 'c';

	std::unordered_map<int, char> std_m;
	std_m[3] = 'c';
}