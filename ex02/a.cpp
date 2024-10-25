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

void binary_insert(const int num, const int range, std::vector<int>& v){

    const int p = std::pow(2, std::ceil( std::log2(range + 0.01)));
    const int v_len = v.size();

    int step;
    int pos;

    pos = (p / 2) - 1 ;
    step = (pos + 1) / 2;

    std::cout << " " << num << " " << range << " " << p << " " << pos <<  " " << step << std::endl;

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

    std::cout << " " << num << " " << range << " " << p << " " << pos <<  " " << step << std::endl;

    v.insert(std::min(v.begin() + pos, v.end()), num);
}

void binary_insert_block(std::vector<int>::const_iterator nums, int range, std::vector<int>& v, const int block){

    const int p = std::pow(2, std::ceil( std::log2(range + 0.01)));
    const int v_len = v.size() / block;

    int step;
    int pos;

    pos = (p / 2) - 1 ;
    step = (pos + 1) / 2;

    std::cout << " " << *nums << " " << range << " " << p << " " << pos <<  " " << step  << " block " << block << std::endl;

    while (step > 0)
    {
        std::cout << pos << ", ";
        if (*nums < v.at(   std::min(block * pos, block * (v_len ))   )    )
            pos -= step;
        else
            pos += step;
        step /= 2; 
    }

    std::cout << pos << ", ";
    if (*nums < v.at(std::min(block * pos, block * (v_len))))
        (void)0;
    else
        pos += 1;

    std::cout << pos << ", \n";

    std::cout << " " << *nums << " " << range << " " << p << " " << pos <<  " " << step  << " block " << block << std::endl;
    v.insert(std::min(v.begin() + pos, v.end()), nums, nums + block);

}

void move_range(std::vector<int>::iterator a, std::vector<int>::iterator b, int block_length)
{
    for (int i = 0; i < block_length; i++)
        std::swap(*(a + i), *(b + i));
}

void pair_up(std::vector<int> &vec_unsorted)
{
    for (int block = 1; vec_unsorted.size() / block > 1; block *= 2)
    {
        for (int i = 0; i + block < vec_unsorted.size(); i += 2*block)
        {
            if (vec_unsorted.at(i) < vec_unsorted.at(i + block))
                move_range(vec_unsorted.begin() + i, vec_unsorted.begin() + i + block, block);
        }
        std::cout << "vec_unsorted " << vec_unsorted << '\n' << std::endl;

    } 
}

void multiple_binary_insert(const std::vector<int> &vec_unsorted, std::vector<int> &vec)
{
    int low = 0;
    int high = 1;
    const int vec_len = vec_unsorted.size();

    int stop_bound = 20;

    for (int k = 1; k < stop_bound; k++){
        high = (std::pow(2, k+1) + std::pow(-1, k)) / 3;
        for (int i = high; i > low; i--)
        {
            if (vec_len > i * 2 - 1){
                binary_insert(vec_unsorted.at( i * 2 - 1), std::pow(2, k), vec);
            }
            else
                stop_bound = k;
        }
        low = high;
    }
}

void multiple_binary_insert_block(const std::vector<int> &vec_unsorted, std::vector<int> &vec, const int block)
{
    int low = 0;
    int high = 1;
    const int vec_len = vec_unsorted.size();

    int stop_bound = 20;

    for (int k = 1; k < stop_bound; k++){
        high = (std::pow(2, k+1) + std::pow(-1, k)) / 3;
        for (int i = high; i > low; i--)
        {
            if (vec_len > i * 2 - 1){
                binary_insert_block(vec_unsorted.begin() + ( i * 2 - 1), std::pow(2, k) - 1, vec, block);
            }
            else
                stop_bound = k;
        }
        low = high;
    }
}

int main(int argc, char const *argv[])
{
    const int vector_length = 8;
    // std::srand(std::time(nullptr));
    std::srand(16);
    
    std::vector<int> vec_unsorted;

    // Fill vector with random integers
    for (int i = 0; i < vector_length; i++){
        vec_unsorted.push_back(randint(0, 99));
    }
    std::cout << "unsorted " << vec_unsorted << '\n' << std::endl;

    pair_up(vec_unsorted);
    std::cout << "paired   " << vec_unsorted << '\n' << std::endl;


    move_range(vec_unsorted.begin(), vec_unsorted.begin() + 4, 4);
    std::cout << "moveed   " << vec_unsorted << '\n' << std::endl;


    std::vector<int> vec;

    // multiple_binary_insert(vec_unsorted, vec);

    for (int i = 0; i + 1 < vec_unsorted.size(); i++){
        if (i % 4 == 0){
            vec.push_back(vec_unsorted.at(i    ));
            vec.push_back(vec_unsorted.at(i + 1));

        }
    }
    std::cout << "vec      " << vec << '\n' << std::endl;
    // multiple_binary_insert_block(vec_unsorted, vec, 2);

    binary_insert_block(vec_unsorted.begin() + 2, 1, vec, 2);
    // vec.insert(vec.begin(), vec_unsorted.begin() + 2, vec_unsorted.begin() + 4);
    std::cout << "vec      " << vec << '\n' << std::endl;

    //                  what         , where roughtly, where to, blocksize
    binary_insert_block(vec_unsorted.begin() + 6, 3, vec, 2);
    // vec.insert(vec.end() - 2, vec_unsorted.begin() + 6, vec_unsorted.begin() + 8);
    std::cout << "vec      " << vec << '\n' << std::endl;

    vec_unsorted.clear();
    vec_unsorted.swap(vec);
    vec.clear();

    std::cout << "vec      " << vec << '\n' << std::endl;
    std::cout << "uns      " << vec_unsorted << '\n' << std::endl;

    for (int i = 0; i < vec_unsorted.size(); i++){
        if (i % 2 == 0)
            vec.push_back(vec_unsorted.at(i));}
    std::cout << "vec      " << vec << '\n' << std::endl;

    // multiple_binary_insert_block(vec_unsorted, vec, 1);
    multiple_binary_insert(vec_unsorted, vec);
    std::cout << "vec      " << vec << '\n' << std::endl;

    if (std::is_sorted(std::begin(vec), std::end(vec)))
        std::cout << "OK" << std::endl;
    else
        std::cout << "┌─────┐\n│ERROR│\n└─────┘" << std::endl;
    return 0;
}
