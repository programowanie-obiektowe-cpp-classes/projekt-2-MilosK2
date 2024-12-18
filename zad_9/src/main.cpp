#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>

int main()
{
    std::ifstream data("../../../aoc9.txt");
    std::string   buff;
    std::vector<long int > numbers;

    while (std::getline(data, buff))
        numbers.push_back(std::stoll(buff));
    
    bool done = 0;
    bool ok   = 0;
    int  it=25;
    while (!done) {
        ok = 0;
        for (int i = it - 25; i < it-1; i++) {
            for (int j = i + 1; j < it; j++)
                if (numbers.at(i) + numbers.at(j) == numbers.at(it))
                    ok = true;
        }
        if (!ok)
            done = true;
        it++;
    }

    long long int first = numbers.at(it - 1);
    std::cout << first<<std::endl;

    bool success        = 0;
    long long int final_sum=0;

    auto find_sum = [&](std::ranges::viewable_range auto&& r) {
        long long int sum = std::accumulate(r.begin(), r.end(), 0);
        if (sum == first and success == false)
        {
            final_sum = std::ranges::max(r) + std::ranges::min(r);
            return true;
        }
            else return false;
        
    };

    for (int i = 3; i < 800; i++) {
        auto view    = numbers | std::views::slide(i) | std::ranges::views::common;
        std::find_if(view.begin(), view.end(), find_sum);
    }
    std::cout << final_sum << std::endl;
}
