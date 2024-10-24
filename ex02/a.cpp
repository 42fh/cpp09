#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <iomanip> 
#include <ctime>
#include <algorithm>

int randint(int lower, int higher)
{
    int random_value = (std::rand() % (higher - lower)) + lower;
    return random_value;
}

std::ostream& operator<<(std::ostream &os, const std::vector<int> v)
{
    for (const int i : v) {
        os << i << ", ";
    }
    return os;
}

void binary_insert(const int num, int range, std::vector<int>& v){

    int p = std::pow(2, std::ceil( std::log2(range + 0.01)));
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
    const int vector_length = 300;
    std::srand(std::time(nullptr));
    // std::srand(5);
    
    std::vector<int> vec_semi_sorted;

    for (int i = 10; i < 10 + vector_length; i++){
        if (i % 2 == 0)
            vec_semi_sorted.push_back(i);
        else
            vec_semi_sorted.push_back(randint(i - 10, i - 1  ));
    }
    std::cout << vec_semi_sorted << '\n' << std::endl;

    // printing
    {
        std::cout << std::setw(2);

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


    std::vector<int> vec;
    for (int i = 0; i < vector_length; i++){
        if (i % 2 == 0)
            vec.push_back(vec_semi_sorted.at(i));
    }


    // 1 3 2 5 4 11 10 9 8 7 6 ...
    int low = 0;
    int high = 1;
    const int vec_len = vec_semi_sorted.size();

    int insertion_range = 3;
    int stop_bound = 20;
    for (int k = 1; k < stop_bound; k++){
        high = (std::pow(2, k+1) + std::pow(-1, k)) / 3;
        for (int i = high; i > low; i--)
        {
            if (vec_len > i * 2 - 1){
                binary_insert(vec_semi_sorted.at( i * 2 - 1), std::pow(2, k) - 1, vec);
                // binary_insert(vec_semi_sorted.at( i * 2 - 1), insertion_range, vec);
                insertion_range += 1;
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
