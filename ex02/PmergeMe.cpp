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

// swaps the n values starting at p1 and p2, 
// for n == 1 it is just swapping two values
static void nswap(vii p1, vii p2, const uint n)
{
    for (uint c = 0; c < n; c++)
        {
            fh::swap(*p1, *p2);
            ++p1;
            ++p2;
        }
}

static void sort_n_block(std::vector<int> &vec, uint n)
{
    vii prev;
    for (vii i = vec.begin(); i < vec.end(); i += n)
    {
        prev = i;
        i += n;
        if (i >= vec.end())
            break ;

        if (*prev > *i)
            nswap(prev, i, n);
    }
}


// sorting of 21 elements, for practice, replication of Knuth book
void fh::sort_v_21(std::vector<int>& vec)
{
    std::cout << "running sort_v_21\n";


    // block sorting of size 1, i.e. we move one number at once
    // {
    //     vii prev;
    //     for (vii i = vec.begin(); i < vec.end(); i += 1)
    //     {
    //         prev = i;
    //         i += 1;
    //         if (i >= vec.end())
    //             break ;
    
    //         if (*prev > *i)
    //             nswap(prev, i, 1);
    //     }
    // }
    sort_n_block(vec, 1);

    
    std::cout << "intermediate step:\n";
    out << vec;
    
    // block sorting of size 1, i.e. we move one number at once
    // {
    //     vii prev;
    //     for (vii i = vec.begin(); i < vec.end(); i += 2)
    //     {
    //         prev = i;
    //         i += 2;
    //         if (i >= vec.end())
    //             break ;

    //         if (*prev > *i)
    //             nswap(prev, i, 2);
    //     }
    // }
    sort_n_block(vec, 2);


    
}


void PmergeMe::sort_v(std::vector<int>& vec)
{
    std::cerr << "sort_v \n";
    unsigned int n = std::distance(vec.begin(), vec.end());

    if (n == 0)
        return ;
    else if (n == 1)
        return ;
    else if (n == 2)
    {
        fh::sort_v_2(vec);
        return ;
    }
    else if (n == 3)
    {
        fh::sort_v_3(vec);
        return ;
    }
    else if (n == 21)
    {
        fh::sort_v_21(vec);
        return ;
    }

    std::vector < std::vector<int> > vv;
    int prev;
    std::vector<int> leftover;
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::vector<int> tmp;
        prev = *it;
        it += 1;
        if (it != vec.end())
        {
            if (prev < *it)
            {
                tmp.push_back(prev);
                tmp.push_back(*it);
                vv.push_back(tmp);
            }
            else
            {
                tmp.push_back(*it);
                tmp.push_back(prev);
                vv.push_back(tmp);
            }
        }
        else
        {
            leftover.push_back(prev);
            break ;
        }
    }

    fh::sort(vv);

    // insert second element of last pair to main chain
    {
        std::vector<int>& r = vv.back();
        int n = r.back();
        r.pop_back();
        std::vector<int> tmp;
        tmp.push_back(n);
        vv.push_back(tmp);
    }

    
    
    if (leftover.size() > 0)
        vv.push_back(leftover);
    
    std::cout << "vv = " << vv << '\n';
}

// ------------ Helper functions

std::ostream& operator<<(std::ostream& o, const std::vector<int>& v)
{
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
        o << *it << ", ";
    return (o);
}

