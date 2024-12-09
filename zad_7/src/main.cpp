//#include "PrintHello.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

class BagCount
{public:
    std::string name;
    int         count = 0;
};

class Bag
{
public:
    Bag(std::string name_) : name(name_){};
    std::string                name;
    int                        count = 0;
    std::vector< BagCount > hide_bags;
    bool                       end_flag_=0;

    void propagate(std::unordered_map< std::string, Bag >& bags, bool& end_flag)
    {
        if (!end_flag)
        {
            for (auto& e : hide_bags)
            {
                if (end_flag)
                    break;

                auto ref = &bags.at(e.name);
                ref->count++;
                if (e.name == "shiny gold")
                {
                    end_flag = 1;
                    break;
                }
                else
                    ref->propagate(bags, end_flag);
            }
        }
    }
    void how_many_inside(std::unordered_map< std::string, Bag >& bags, int& how_many, int multiply)
    {
        for (auto& e : hide_bags)
        { 
            how_many += multiply*e.count;
            auto ref = &bags.at(e.name);
            ref->how_many_inside(bags, how_many, multiply * e.count);
        }
    } 
    };

bool isNumber(const std::string& str)
{
    for (char c : str)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
};
bool check_word(std::string word)
{
    int res = 1;
    if (word.contains("bag") || word.contains("contain") || word.contains("no") || word.contains("other"))
        res = 0;

    return res;
};
std::vector< std::string > split_sentence(std::string sen)
{
    std::stringstream ss(sen);
    std::string       word;

    std::vector< std::string > words;

    while (ss >> word)
    {
        if (check_word(word))
            words.push_back(word);
    }

    return words;
};
int main()
{
    std::unordered_map< std::string, Bag > bags;
    std::ifstream data("C:/Users/Lenovo/Desktop/Studia/Cpp/projekt-2-MilosK2/zad_7/aoc7.txt");
    std::string   buff;

    while (std::getline(data, buff))
    {
        std::vector< std::string > names = split_sentence(buff);

        Bag aux_bag(names[0] + " " + names[1]);

        int i = 2;
        while (i < names.size())
        {
            BagCount temp;
            temp.name = names.at(i + 1) + " " + names.at(i + 2);
            temp.count = std::stoi(names.at(i));
            aux_bag.hide_bags.push_back(std::move(temp));
            i += 3;
        }
        bags.insert({aux_bag.name, std::move(aux_bag)});
    }

    for (auto& e : bags)
        e.second.propagate(bags, e.second.end_flag_);

    std::cout << bags.at("shiny gold").count<<std::endl;

   int how_many_inside = 0;

    bags.at("shiny gold").how_many_inside(bags, how_many_inside, 1);

    std::cout << how_many_inside;


    return 0;
}
