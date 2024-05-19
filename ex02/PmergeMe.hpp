#pragma once
#include <vector>

#include <iostream>

// Helper functions
std::ostream& operator<<(std::ostream& o, std::vector<int> v);

namespace fh {
    
    template <typename T>
    void swap(T& a, T&b)
    {
        const T tmp = a;
    
        a = b;
        b = tmp;
    }
    
    template <typename T>
    bool issorted(const typename T::const_iterator& b, const typename T::const_iterator& e)
    {
        if (b == e)
            return (true);
        
        typename T::const_iterator it = b;
        typename T::const_iterator prev = it++;
        
        while (it != e)
        {
            if (*prev > *it)
                return (false);
            prev = it++;
        }
        return (true);
    }
    
    template <typename T>
    void sort(const typename T::iterator begin, const typename T::iterator end)
    {
        while (!issorted< T >(begin, end))
        {
            typename T::iterator it = begin;
            typename T::iterator prev = it++;
    
            while (it != end)
            {
                if (*prev > *it)
                    fh::swap(*prev, *it);
                prev = it++;
            }
        }
    }


}





class PmergeMe
{
private:
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);

public:
    PmergeMe();
    ~PmergeMe();

    static void sort_vec(std::vector<int>::iterator, std::vector<int>::iterator);

    template <typename T>
    static void sort_with_vec(typename T::iterator begin, typename T::iterator end);
};

template <typename T>
void PmergeMe::sort_with_vec(typename T::iterator begin, typename T::iterator end)
{
    std::vector<int> v;
    
    for(typename T::iterator it = begin; it != end; ++it){ 
        v.push_back(*it); }
    
    PmergeMe::sort_vec(v.begin(), v.end());

    // copy result back
    typename T::iterator it = begin;
    std::vector<int>::iterator jt = v.begin();
    
    while (it != end && jt != v.end()){
        *it = *jt;
        ++it;
        ++jt;
    }   
}