#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>


#include "PmergeMe.hpp"



static bool isdig(char *str)
{
    while (*str)
    {
        if (std::isdigit(*str) == 0) return (false);
        str++;
    }
    return (true);
}

static std::vector<int> validate_input(int c, char **v)
{
    std::vector<int> ret;

    for (int i = 1; i < c; i++)
    {
        if (!isdig(v[i]))
            throw std::runtime_error("invalid number (contains non digits)");
        int tmp = atoi(v[i]);
        if (tmp < 0)
            throw std::runtime_error("invalid number (no negative numbers allowed)");
        ret.push_back(tmp);
    }
    std::set<int> retset(ret.begin(), ret.end());
    if (retset.size() != ret.size())
        throw std::runtime_error("no duplicates allowed");
    return (ret);
}

int main(int c, char **v)
{
    if (c < 2){
        std::cerr << "Error: no input provided\n"; return(1); }


    std::vector<int> input;
    try {
        input = validate_input(c, v);
    }
    catch (std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "provided input:\n" << input << '\n';
    std::cout << "is sorted input: " << fh::issorted< std::vector<int> >(input.begin(), input.end()) << '\n';
    
    // PmergeMe< std::vector<int> > a(input.begin(), input.end());
    // PmergeMe< std::vector<int> > a;

    PmergeMe::sort_with_vec< std::vector<int> >(input.begin(), input.end());

    std::cout << "sorted input:\n" << input << '\n';
    std::cout << "is sorted input: " << fh::issorted< std::vector<int> >(input.begin(), input.end()) << '\n';

}