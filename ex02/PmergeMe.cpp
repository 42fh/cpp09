#include "PmergeMe.hpp"

#include <algorithm>

PmergeMe::PmergeMe(const PmergeMe& other)
{
    (void) other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void) other;
    return *this;
}

PmergeMe::~PmergeMe()
{
}

static void sort_vec_2(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    (void) end;
    if (*begin > *(begin + 1))
        fh::swap(*begin, *(begin + 1));
}

// [a, b, c]
// a, b, c
// a', b', c
// a <-- b,   c
// __ a <--  __  b __,   c
// three slots, 2 comparisons
static void sort_vec_3(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    (void) end;
    std::vector<int>::iterator mid = begin + 1;
    std::vector<int>::iterator last = begin + 2;

    // order the first two
    if (*begin > *mid)
        fh::swap(*begin, *mid);
    
    //insert last
    if (*last < *begin) // last is smallest
    {
        fh::swap(*last, *mid);
        fh::swap(*mid, *begin);
    }
    else if (*last < *mid) // last is between begin and mid
    {
        fh::swap(*last, *mid);
    }
}


void PmergeMe::sort_vec(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    unsigned int n = std::distance(begin, end);
    
    switch (n) {
        case 0: break ;
        case 1: break ;
        case 2: sort_vec_2(begin, end); break ;
        case 3: sort_vec_3(begin, end); break ;
        default: fh::sort< std::vector<int> >(begin, end); break ;
    }
}


// ------------ Helper functions

std::ostream& operator<<(std::ostream& o, std::vector<int> v)
{
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
        o << *it << ", ";
    return (o);
}

