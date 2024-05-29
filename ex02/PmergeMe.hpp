#pragma once
#include <vector>
#include <iostream>


// typedefs
typedef std::vector<int>::iterator vii;


#define out std::cout


// Helper functions
std::ostream& operator<<(std::ostream& o, const std::vector<int>& v);

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& v)
{
    for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        o << "[ " << *it << " ]" << '\n';
    }
    return o;
}


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

    template <typename T>
    void sort(T& vec)
    {
        sort(vec.begin(), vec.end());
    }
    
    template <typename T>
    void sort_v_2(std::vector<T>& vec)
    {
        if (vec.at(0) > vec.at(1))
            fh::swap(vec.at(0), vec.at(1));
    }

    // [a, b, c]
    // a, b, c
    // a', b', c
    // a <-- b,   c
    // __ a <--  __  b __,   c
    // three slots, 2 comparisons
    template <typename T>
    void sort_v_3(std::vector<T>& vec)
    {
        typename std::vector<T>::iterator begin = vec.begin();
        typename std::vector<T>::iterator mid = begin + 1;
        typename std::vector<T>::iterator last = begin + 2;

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

    void sort_v_21(std::vector<int>& vec);

    
}





class PmergeMe
{
private:
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);

public:
    PmergeMe();
    ~PmergeMe();

    static void sort_v(std::vector<int>& vec);

    template <typename T>
    static void sort_v(std::vector<T>& vec);

    template <typename T>
    static void sort_with_vec(typename T::iterator begin, typename T::iterator end);
};




template <typename T>
static void sort_v(std::vector<T>& vec)
{
    fh::sort(vec.begin(), vec.end());
}

template <typename T>
void PmergeMe::sort_with_vec(typename T::iterator begin, typename T::iterator end)
{
    std::vector<int> v;
    
    for(typename T::iterator it = begin; it != end; ++it){ 
        v.push_back(*it); }
    
    PmergeMe::sort_v(v);

    // copy result back
    typename T::iterator it = begin;
    std::vector<int>::iterator jt = v.begin();
    
    while (it != end && jt != v.end()){
        *it = *jt;
        ++it;
        ++jt;
    }   
}