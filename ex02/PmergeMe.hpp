#pragma once

class PmergeMe
{
private:
    PmergeMe(PmergeMe& other);
    PmergeMe& operator=(PmergeMe& other);

public:
    PmergeMe();
    ~PmergeMe();
};