#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include "PmergeMe.hpp"
#include <iomanip>

int sort_using_vector(int c, char **v);
int sort_using_deque(int c, char **v);


int main(int c, char **v)
{
    sort_using_vector(c, v);
    sort_using_deque(c, v);
    return 42;
}



int sort_using_vector(int c, char **v)
{
    if (c < 2)
    {
        std::cerr << "Error: no input provided\n";
        return (1);
    }

    std::vector<int> input;
    try
    {
        input = validate_input(c, v);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    clock_t start_vector = clock();

    OS << "Before:\t" << input;

    const t_iv random_vector = input;
    const t_iv pair_vector = make_pairs_of_pairs(random_vector);

    const unsigned int biggest_smaller_power = calculate_biggest_block(pair_vector);

    t_iv before(pair_vector);
    for (unsigned int block_size = biggest_smaller_power / 2; block_size > 0; block_size /= 2)
    {

        block_vector bs_blocks(before, block_size);
        t_iv bs_all_a_s = bs_blocks.get_all_A_blocks();
        block_vector bs_all_a_s_BV(bs_all_a_s, block_size);

        bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);
        const int delta = before.size() - bs_all_a_s_BV.getVector().size();
        bs_all_a_s_BV.insert_raw(before.end() - delta, before.end());

        before.clear();
        before = bs_all_a_s_BV.getVector();
    }

    clock_t end_vector = clock();

    final_check_and_msg(before);

    OS << "Time to process a using std::vector : " << double(end_vector - start_vector) / double(CLOCKS_PER_SEC) << EL;

    return 0;
}

int sort_using_deque(int c, char **v)
{
    if (c < 2)
    {
        std::cerr << "Error: no input provided\n";
        return (1);
    }

    std::deque<int> input;
    try
    {
        input = validate_input_deque(c, v);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    clock_t start_deque = clock();

    const t_id random_deque = input;
    const t_id pair_deque = make_pairs_of_pairs(random_deque);

    const unsigned int biggest_smaller_power = calculate_biggest_block(pair_deque);

    t_id before(pair_deque);
    for (unsigned int block_size = biggest_smaller_power / 2; block_size > 0; block_size /= 2)
    {

        block_deque bs_blocks(before, block_size);
        t_id bs_all_a_s = bs_blocks.get_all_A_blocks();
        block_deque bs_all_a_s_BV(bs_all_a_s, block_size);

        bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);

        const int delta = before.size() - bs_all_a_s_BV.getDeque().size();
        bs_all_a_s_BV.insert_raw(before.end() - delta, before.end());

        before.clear();
        before = bs_all_a_s_BV.getDeque();
    }

    clock_t end_deque = clock();

    final_check_and_msg(before);

    OS << "Time to process a using std::deque  : " << double(end_deque - start_deque) / double(CLOCKS_PER_SEC) << EL;

    return 0;
}
