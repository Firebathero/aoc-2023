#include <vector>
#include <iostream>
#include <fstream>

#include <range/v3/all.hpp>


int main()
{
    constexpr int coefficient = 999999;
    std::vector<std::pair<int, int>> stars;

    std::ifstream file("input.txt");
    std::string line;
    for (int y{}; std::getline(file, line); y++)
        if (auto x = line | ranges::views::enumerate | ranges::views::filter([](auto p) { return p.second == '#'; }) | ranges::views::keys; ranges::empty(x))
            y += coefficient;
        else
            stars |= ranges::actions::push_back(ranges::views::zip(x, ranges::views::repeat(y)));

    for (const auto& star : stars) {
        std::cout << "Star at: " << star.first << ", " << star.second << std::endl;
    }

    auto gaps = (stars |= ranges::actions::sort) | ranges::views::keys | ranges::views::unique | ranges::to<std::vector>();
    for (int k{}; auto& star : stars | ranges::views::keys)
    star += (star - (k += gaps[k] < star)) * coefficient;

    long long result{};
    for (int k{}; auto [x1, y1] : stars)
    for (auto [x2, y2] : stars | ranges::views::drop(++k))
        result += std::abs(x1 - x2) + std::abs(y1 - y2);
    std::cout << result << '\n';
}
