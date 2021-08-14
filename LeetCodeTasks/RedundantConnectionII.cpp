#include <vector>
#include <queue>
#include <tuple>
#include <stack>

namespace
{
    class Solution 
    {
    public:
        std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>>& edges)
        {
            int root;
            std::vector<std::vector<int>> adj_list;
            std::tie(root, adj_list) = build_weighted(edges);

            //UF uf(edges.size() + 1);
            std::stack<int> stk;
            stk.push(root);
        }
    private:
        std::tuple< int, std::vector<std::vector<int>> > build_weighted(std::vector<std::vector<int>>& edges)
        {

        }

        struct UF
        {
            UF(int N);
        };
    };
}

void RedundantConnectionII()
{

}