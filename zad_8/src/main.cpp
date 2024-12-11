#include "PrintHello.hpp"
#include <vector>
#include<string>
#include<iostream>
#include <fstream>

class Step
{public:
    std::string type      = "";
    bool        visited   = 0;
    int           value   = 0;

};

int first(std::vector< Step >& steps)
{
    int  accumulator = 0;
    bool done        = 0;
    int  position    = 0;
    int  size        = steps.size();

    while (!done)
    {

        steps.at(position).visited = true;

        if (steps.at(position).type == "acc")
        {
            accumulator += steps.at(position).value;
            position += 1;
        }
        else if (steps.at(position).type == "jmp")
            position += steps.at(position).value;
        else if (steps.at(position).type == "nop")
            position += 1;
        else
            std::cout << "Type reading error\n";

        if (steps.at(position).visited == true)
            done = true;
    }
    return accumulator;
}

bool second(std::vector< Step >& steps, int& accumulator)
{
    bool done        = 0;
    bool found       = 0;
    int  position    = 0;
    int  size        = steps.size();
    accumulator      = 0;

    while (!done)
    {
        steps.at(position).visited = true;

        if (steps.at(position).type == "acc")
        {
            accumulator += steps.at(position).value;
            position += 1;
        }
        else if (steps.at(position).type == "jmp")
            position += steps.at(position).value;
        else if (steps.at(position).type == "nop")
            position += 1;
        else
            std::cout << "Type reading error\n";

        if (position >= steps.size()) {
            found = 1;
            done = true;
        }
        else if (steps.at(position).visited == true)
            done = true;
    }
    return found;
}

int main()
{
    std::vector< Step > steps;
    std::ifstream       data("../../../aoc8.txt");
    std::string         buff;

    while (std::getline(data, buff))
    {
        Step step;
        step.type = buff.substr(0, 3);

        step.value = std::stoi(buff.substr(4, buff.size()));

        steps.push_back(std::move(step));
    }

    std::cout << first(steps) << std::endl;
    int accumulator=0;
    
    for (auto& e : steps)
    {
        for (auto& e : steps)
            e.visited = 0;

        if (e.type == "jmp")
            e.type = "nop";
        else if (e.type == "nop")
            e.type = "jmp";

        if (second(steps, accumulator))
            break;
        else
        {
            if (e.type == "jmp")
                e.type = "nop";
            else if (e.type == "nop")
                e.type = "jmp";
        }
    }
    std::cout << accumulator;
}
