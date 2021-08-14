#include <vector>
#include <string>

namespace
{
	class Solution 
	{
	public:
		std::vector<std::string> generateParenthesis(int n)
		{
			if (n == 0)
				return { "" };

			auto balance = 0;
			m_size = 2 * n;
			m_res.clear();
			std::string candidate(m_size, '?');
			generate(0, candidate, balance);
			return m_res;
		}
	private:
		void generate(int i, std::string& candidate, int balance)
		{
			if (i == m_size)
			{
				if (balance == 0)
					m_res.push_back(candidate);
				return;
			}

			if (balance == 0)
			{
				candidate[i] = '(';
				generate(i + 1, candidate, balance + 1);
			}
			else
			{
				candidate[i] = '(';
				generate(i + 1, candidate, balance + 1);

				candidate[i] = ')';
				generate(i + 1, candidate, balance - 1);
			}

		}

		int m_size{ -1 };
		std::vector<std::string> m_res;
	};
}

void GenerateParentheses()
{

}