// g++ -std=c++20 reservoir.cpp -o reservoir && ./reservoir < input
#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <regex>
#include <set>
#include <string>
#include <vector>

using Point = std::pair<int, int>;

int signum(int const x)
{
    if (x == 0)
    {
        return 0;
    }
    else if (x < 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int main()
{
    std::string s;
    std::set<Point> rock;
    std::regex const points{"(\\d+),(\\d+)"};
    std::smatch match;
    while (std::getline(std::cin, s))
    {
        auto b = s.cbegin();
        auto const e = s.cend();

        std::regex_search(b, e, match, points);

        int x, y;
        x = std::stoi(match[1]);
        y = std::stoi(match[2]);
        rock.insert(Point{x, y});

        b = std::find(b, e, '>');
        while (b != e)
        {
            b = std::next(b);
            std::regex_search(b, e, match, points);
            int const nx = std::stoi(match[1]);
            int const ny = std::stoi(match[2]);

            int const dx = signum(nx - x);
            int const dy = signum(ny - y);

            while (x != nx || y != ny)
            {
                x += dx;
                y += dy;

                rock.insert(Point{x, y});
            }

            b = std::find(b, e, '>');
        }
    }

    int const yabyss = std::accumulate(rock.cbegin(),
                                       rock.end(),
                                       0,
                                       [](int const acc, auto const& point) {
                                           return std::max(acc, point.second);
                                       });

    auto nextMove = [&](Point const& sand) -> std::optional<Point> {
        if (rock.count({sand.first, sand.second + 1}) == 0)
        {
            return Point{sand.first, sand.second + 1};
        }
        else if (rock.count({sand.first - 1, sand.second + 1}) == 0)
        {
            return Point{sand.first - 1, sand.second + 1};
        }
        else if (rock.count({sand.first + 1, sand.second + 1}) == 0)
        {
            return Point{sand.first + 1, sand.second + 1};
        }
        else
        {
            return std::nullopt;
        }
    };

    int numGrains = 0;
    while (true)
    {
        Point sand{500, 0};

        while (auto next = nextMove(sand))
        {
            sand = *next;
            if (sand.second >= yabyss)
            {
                std::cout << numGrains << "\n";
                exit(EXIT_SUCCESS);
            }
        }

        rock.insert(sand);
        ++numGrains;
    }
}
