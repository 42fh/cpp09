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

    int p = std::pow(2, std::ceil( std::log2(range + 0.1)));

    int step;
    int pos;

    pos = (p / 2) - 1 ;
    step = (pos + 1) / 2;
    std::cout << step << ' ' << pos << ' ' << p << ' ' << range <<std::endl;

    while (step > 0)
    {
        if (num < v.at(pos))
            pos -= step;
        else
            pos += step;
        step /= 2; 
    }
    if (num < v.at(pos))
        (void)0;
    else
        pos += 1;

    v.insert(v.begin() + pos, num);
}

int main(int argc, char const *argv[])
{
    // std::srand(std::time(nullptr));
    std::srand(5);
    
    std::vector<int> vec_semi_sorted;

    for (int i = 10; i < 30; i++){
        if (i % 2 == 0)
            vec_semi_sorted.push_back(i);
        else
            vec_semi_sorted.push_back(randint(i - 7, i - 1  ));
    }
    std::cout << vec_semi_sorted << '\n' << std::endl;

    {
        std::cout << std::setw(2);

        for (size_t i = 0; i < 20; i++){
            if (i % 2 == 0)
                std::cout << std::setw(2) << vec_semi_sorted.at(i) << ' ';
        }
        std::cout << '\n';
        for (size_t i = 0; i < 20; i++){
            if (i % 2 == 1)
                std::cout << " | " ;
        }
        std::cout << '\n';

        for (size_t i = 0; i < 20; i++){
            if (i % 2 == 1)
                std::cout << std::setw(2) << vec_semi_sorted.at(i) << ' ';
        }
        std::cout << "\n\n";

    }


    std::vector<int> vec;
    for (int i = 0; i < 20; i++){
        if (i % 2 == 0)
            vec.push_back(vec_semi_sorted.at(i));
    }


    // 1 3 2 5 4 11 10 9 8 7 6

    vec.insert(vec.begin(), vec_semi_sorted.at(1));
    binary_insert(vec_semi_sorted.at( 3 * 2 - 1), 3, vec);
    binary_insert(vec_semi_sorted.at( 2 * 2 - 1), 4, vec);
    binary_insert(vec_semi_sorted.at( 5 * 2 - 1), 5, vec);
    binary_insert(vec_semi_sorted.at( 4 * 2 - 1), 6, vec);
 // binary_insert(vec_semi_sorted.at(11 * 2 - 1), 7, vec); does not exit
    binary_insert(vec_semi_sorted.at(10 * 2 - 1), 8, vec);
    binary_insert(vec_semi_sorted.at( 9 * 2 - 1), 9, vec);
    binary_insert(vec_semi_sorted.at( 8 * 2 - 1),10, vec);
    binary_insert(vec_semi_sorted.at( 7 * 2 - 1),11, vec);
    binary_insert(vec_semi_sorted.at( 6 * 2 - 1),12, vec);
    

    std::cout << vec << std::endl;

    if (std::is_sorted(std::begin(vec), std::end(vec)))
        std::cout << "OK" << std::endl;
    else
        std::cout << "┌─────┐\n│ERROR│\n└─────┘" << std::endl;



    return 0;
}
