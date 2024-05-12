#include <iostream>
#include <vector>
#include <cstdlib>

// #include "PmergeMe"

std::ostream& operator<<(std::ostream& o, std::vector<int> v)
{
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
        o << *it << ", ";
    return (o);
}

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

    std::cout << input << '\n';

    // PmergeMe a();
}