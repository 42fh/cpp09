#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <iomanip> 
#include <ctime>
#include <algorithm>

// printing
void print_vec(const std::vector<int> &vec_semi_sorted) 
{
    const int vector_length = vec_semi_sorted.size();
    for (size_t i = 0; i < vector_length; i++){
        if (i % 2 == 0)
            std::cout << std::setw(2) << vec_semi_sorted.at(i) << ' ';
    }
    std::cout << '\n';
    for (size_t i = 0; i < vector_length; i++){
        if (i % 2 == 1)
            std::cout << " | " ;
    }
    std::cout << '\n';

    for (size_t i = 0; i < vector_length; i++){
        if (i % 2 == 1)
            std::cout << std::setw(2) << vec_semi_sorted.at(i) << ' ';
    }
    std::cout << "\n\n";

}

int randint(int lower, int higher)
{
    int random_value = (std::rand() % (higher - lower)) + lower;
    return random_value;
}

std::ostream& operator<<(std::ostream &os, const std::vector<int> v)
{
    int count = 0;
    for (const int i : v) {
        if (count < 20)
            os << i << ", ";
        count += 1;
    }
    if (count >= 20)
        os << " ... " << "(" << v.size() << " total)";
    return os;
}

void binary_insert(const int num, int range, std::vector<int>& v){

    const int p = std::pow(2, std::ceil( std::log2(range + 0.01)));
    const int v_len = v.size();

    int step;
    int pos;

    pos = (p / 2) - 1 ;
    step = (pos + 1) / 2;

    // std::cout << " " << num << " " << range << " " << p << " " << pos <<  " " << step << std::endl;

    while (step > 0)
    {
        if (num < v.at(std::min(pos, v_len - 1)))
            pos -= step;
        else
            pos += step;
        step /= 2; 
    }
    if (num < v.at(std::min(pos, v_len - 1)))
        (void)0;
    else
        pos += 1;

    v.insert(std::min(v.begin() + pos, v.end()), num);
}

int main(int argc, char const *argv[])
{
    const int vector_length = 8;
    // std::srand(std::time(nullptr));
    std::srand(3);
    std::srand(33);
    
    std::vector<int> vec_unsorted;

    for (int i = 0; i < vector_length; i++){
        vec_unsorted.push_back(randint(0, 99));
    }
    std::cout << vec_unsorted << '\n' << std::endl;

    for (int i = 0; i < vec_unsorted.size(); i += 2)
    {
        if (vec_unsorted.at(i) > vec_unsorted.at(i + 1))
            std::swap(vec_unsorted.at(i), vec_unsorted.at(i + 1));
    }

    std::cout << vec_unsorted << '\n' << std::endl;

    for (int i = 0; i < vec_unsorted.size(); i += 4)
    {
        if (vec_unsorted.at(i) > vec_unsorted.at(i + 2))
            std::swap(vec_unsorted.at(i), vec_unsorted.at(i + 2));
            std::swap(vec_unsorted.at(i + 1), vec_unsorted.at(i + 3));
    }

    std::cout << vec_unsorted << '\n' << std::endl;


    for (int i = 0; i < vec_unsorted.size(); i += 8)
    {
        if (vec_unsorted.at(i) > vec_unsorted.at(i + 4))
            std::swap(vec_unsorted.at(i), vec_unsorted.at(i + 4));
            std::swap(vec_unsorted.at(i + 1), vec_unsorted.at(i + 5));
            std::swap(vec_unsorted.at(i + 2), vec_unsorted.at(i + 6));
            std::swap(vec_unsorted.at(i + 3), vec_unsorted.at(i + 7));
    }

    std::cout << vec_unsorted << '\n' << std::endl;

    std::vector<int> vec;
    vec.insert(vec.begin(), 4, -1);

    int low = 0;
    int high = 1;
    const int vec_len = vec_unsorted.size();

    int stop_bound = 20;
    for (int k = 1; k < stop_bound; k++){
        high = (std::pow(2, k+1) + std::pow(-1, k)) / 3;
        for (int i = high; i > low; i--)
        {
            if (vec_len > i * 2 - 1){
                binary_insert(vec_unsorted.at( i * 2 - 1), std::pow(2, k) - 1, vec);
            }
            else
                stop_bound = k;
        }
        low = high;
    }

    std::cout << vec << std::endl;

    if (std::is_sorted(std::begin(vec), std::end(vec)))
        std::cout << "OK" << std::endl;
    else
        std::cout << "┌─────┐\n│ERROR│\n└─────┘" << std::endl;

    return 0;
}
