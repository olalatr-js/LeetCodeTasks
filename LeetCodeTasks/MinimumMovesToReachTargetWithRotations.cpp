#include <vector>
#include <queue>
#include <unordered_set>
#include <cassert>
#include <stdexcept>

namespace
{
class Solution 
{
public:
    int minimumMoves(std::vector<std::vector<int>>& grid)
    {
        m_N = static_cast<int>(grid.size());
        const Position target_pos(m_N - 2, m_N - 1, m_N - 1, m_N - 1, Rotation::hor);
        const Position initial_pos(0, 0, 1, 0, Rotation::hor);
        m_visited.clear();

        std::queue<Position> q;
        m_visited.insert(initial_pos);
        q.push(initial_pos);
        auto path_len = -1;

        while (!q.empty())
        {
            ++path_len;
            const auto N = static_cast<int>(q.size());
            for (auto i = 0; i < N; ++i)
            {
                const auto curr_pos = q.front();
                q.pop();
                if (curr_pos == target_pos)
                    return path_len;

                const auto next_moves = get_possible_moves(curr_pos, grid);
                for (const auto& nm : next_moves)
                {
                    if (m_visited.end() == m_visited.find(nm))
                    {
                        m_visited.insert(nm);
                        q.push(nm);
                    }
                }
            }
        }

        return -1;
    }

private:
    int minimumMoves_correct_but_slow(std::vector<std::vector<int>>& grid) 
    {
        m_N = static_cast<int>(grid.size());
        const Position target_pos(m_N-2, m_N-1, m_N-1, m_N-1, Rotation::hor);
        const Position initial_pos(0, 0, 1, 0, Rotation::hor);
        std::unordered_set<Position, PositionHash> visited;

        std::queue<Position> q;
        visited.insert(initial_pos);
        q.push(initial_pos);
        auto path_len = -1;

        while (!q.empty())
        {
            ++path_len;
            const auto N = static_cast<int>(q.size());
            for (auto i = 0; i < N; ++i)
            {
                const auto curr_pos = q.front();
                q.pop();
                if (curr_pos == target_pos)
                    return path_len;

                const auto next_moves = get_possible_moves_correct_but_slow(curr_pos, grid);
                for (const auto& nm : next_moves)
                {
                    if (visited.end() == visited.find(nm))
                    {
                        visited.insert(nm);
                        q.push(nm);
                    }
                }
            }
        }

        return -1;
    }

private:
    // -------> x
    // | (0, 0)
    // |
    // | y
    enum class Rotation
    {
        hor,
        vert
    };

    struct Point
    {
        Point(int ax, int ay): x(ax), y(ay)
        {}

        int x, y;
    };

    struct Position
    {
        // horizontal p1 p2
        // vertical p1
        //          p2
        Position(int x1, int y1, int x2, int y2, Rotation r):
            p1(x1,y1),
            p2(x2,y2),
            rot(r)
        {}

        bool operator == (const Position& other) const
        {
            return (p1.x == other.p1.x) && (p1.y == other.p1.y) &&
                   (p2.x == other.p2.x) && (p2.y == other.p2.y) &&
                   rot == other.rot;
        }

        Point p1, p2;
        Rotation rot;
    };

    struct PositionHash
    {
        std::size_t operator()(const Position& p) const noexcept
        {
            size_t h = (p.rot == Rotation::hor) ? 17 : 19;
            h += 31 * p.p1.x;
            h += 31 * p.p1.y;
            h += 31 * p.p2.x;
            h += 31 * p.p2.y;

            return h;
        }
    };

    std::vector<Position> get_possible_moves(const Position& curr, const std::vector<std::vector<int>>& grid)
    {
        std::vector<Position> res;

        if (curr.rot == Rotation::hor)
        {
            //one cell to the right
            if (curr.p2.x + 1 < m_N && grid[curr.p2.y][curr.p2.x + 1] == 0)
            {
                const Position candidate(curr.p1.x + 1, curr.p1.y, curr.p2.x + 1, curr.p2.y, Rotation::hor);
                if (m_visited.end() == m_visited.find(candidate))
                {
                    res.push_back(candidate);
                }
            }

            if (curr.p1.y + 1 < m_N &&
                grid[curr.p1.y + 1][curr.p1.x] == 0 && grid[curr.p2.y + 1][curr.p2.x] == 0)
            {
                // down one cell
                Position candidate(curr.p1.x, curr.p1.y + 1, curr.p2.x, curr.p2.y + 1, Rotation::hor);
                if (m_visited.end() == m_visited.find(candidate))
                {
                    res.push_back(candidate);
                }

                // Rotate clockwise if it's in a horizontal position
                candidate = Position(curr.p1.x, curr.p1.y, curr.p1.x, curr.p1.y + 1, Rotation::vert);
                if (m_visited.end() == m_visited.find(candidate))
                {
                    res.push_back(candidate);
                }
            }
        }
        else if (curr.rot == Rotation::vert)
        {
            if (curr.p1.x + 1 < m_N &&
                grid[curr.p1.y][curr.p1.x + 1] == 0 && grid[curr.p2.y][curr.p2.x + 1] == 0)
            {
                //one cell to the right
                Position candidate(curr.p1.x + 1, curr.p1.y, curr.p2.x + 1, curr.p2.y, Rotation::vert);
                if (m_visited.end() == m_visited.find(candidate))
                {
                    res.push_back(candidate);
                }

                // Rotate counterclockwise if it's in a vertical position
                candidate = Position(curr.p1.x, curr.p1.y, curr.p1.x + 1, curr.p1.y, Rotation::hor);
                if (m_visited.end() == m_visited.find(candidate))
                {
                    res.push_back(candidate);
                }
            }

            // Move down one cell
            if (curr.p2.y + 1 < m_N && grid[curr.p2.y + 1][curr.p2.x] == 0)
            {
                Position candidate(curr.p2.x, curr.p2.y, curr.p2.x, curr.p2.y + 1, Rotation::vert);
                if (m_visited.end() == m_visited.find(candidate))
                {
                    res.push_back(candidate);
                }
            }
        }
        else
        {
            throw std::logic_error("Never gets here!!!");
        }

        return res;
    }

    std::vector<Position> get_possible_moves_correct_but_slow(const Position& curr, const std::vector<std::vector<int>>& grid)
    {
        std::vector<Position> res;

        if (curr.rot == Rotation::hor)
        {
            //one cell to the right
            if (curr.p2.x + 1 < m_N && grid[curr.p2.y][curr.p2.x + 1] == 0)
                res.emplace_back(curr.p1.x + 1, curr.p1.y, curr.p2.x + 1, curr.p2.y, Rotation::hor);

            if (curr.p1.y + 1 < m_N &&
                grid[curr.p1.y + 1][curr.p1.x] == 0 && grid[curr.p2.y + 1][curr.p2.x] == 0)
            {
                // down one cell
                res.emplace_back(curr.p1.x, curr.p1.y + 1, curr.p2.x, curr.p2.y + 1, Rotation::hor);

                // Rotate clockwise if it's in a horizontal position
                res.emplace_back(curr.p1.x, curr.p1.y, curr.p1.x, curr.p1.y + 1, Rotation::vert);
            }
        }
        else if (curr.rot == Rotation::vert)
        {
            if (curr.p1.x + 1 < m_N &&
                grid[curr.p1.y][curr.p1.x + 1] == 0 && grid[curr.p2.y][curr.p2.x + 1] == 0)
            {
                //one cell to the right
                res.emplace_back(curr.p1.x + 1, curr.p1.y, curr.p2.x + 1, curr.p2.y, Rotation::vert);

                // Rotate counterclockwise if it's in a vertical position
                res.emplace_back(curr.p1.x, curr.p1.y, curr.p1.x + 1, curr.p1.y, Rotation::hor);
            }

            // Move down one cell
            if (curr.p2.y + 1 < m_N && grid[curr.p2.y + 1][curr.p2.x] == 0)
            {
                res.emplace_back(curr.p2.x, curr.p2.y, curr.p2.x, curr.p2.y + 1, Rotation::vert);
            }
        }
        else
        {
            throw std::logic_error("Never gets here!!!");
        }

        return res;
    }

    int m_N;
    std::unordered_set<Position, PositionHash> m_visited;
};
}

void MinimumMovesToReachTargetWithRotations()
{
    Solution sol;
    std::vector<std::vector<int>> grid{ {0, 0, 0, 0, 0, 1},
                                        {1, 1, 0, 0, 1, 0},
                                        {0, 0, 0, 0, 1, 1},
                                        {0, 0, 1, 0, 1, 0},
                                        {0, 1, 1, 0, 0, 0},
                                        {0, 1, 1, 0, 0, 0} };
    auto res = sol.minimumMoves(grid);
    assert(11 == res);

    grid = {{0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 1},
        {1, 1, 1, 0, 0, 1},
        {1, 1, 1, 0, 0, 0}};
    res = sol.minimumMoves(grid);
    assert(9 == res);

    grid = { { 0, 0, 0 },
             { 1, 0, 0 },
             { 1, 0, 0} };
    res = sol.minimumMoves(grid);
    assert(res == 3);

    grid = { {0,0,1},
             {0,0,1},
             {0,0,0} };
    res = sol.minimumMoves(grid);
    assert(res == 3);

    grid = { {0,0,1,0,0},
             {0,0,1,0,0},
             {0,1,0,0,0},
             {0,0,0,0,0},
             {0,0,1,0,0} };
    res = sol.minimumMoves(grid);
    assert(res == 9);
}