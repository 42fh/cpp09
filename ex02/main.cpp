#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include "PmergeMe.hpp"
#include <iomanip>

static bool is_digit(char *str)
{
    while (*str)
    {
        if (std::isdigit(*str) == 0) return (false);
        str++;
    }
    return (true);
}

static std::vector<int> validate_input(int c, char **v)
{
    std::vector<int> ret;

    for (int i = 1; i < c; i++)
    {
        if (!is_digit(v[i]))
            throw std::runtime_error("invalid number (contains non digits)");
        int tmp = atoi(v[i]);
        if (tmp < 0)
            throw std::runtime_error("invalid number (no negative numbers allowed)");
        ret.push_back(tmp);
    }
    std::set<int> retset(ret.begin(), ret.end());
    if (retset.size() != ret.size())
        throw std::runtime_error("no duplicates allowed");
    return (ret);
}

int main(int c, char **v)
{
    if (c < 2){
        std::cerr << "Error: no input provided\n"; return(1); }


    std::vector<int> input;
    try {
        input = validate_input(c, v);
    }
    catch (std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "provided input:\n" << input << '\n';

	// ---- old vs new

	// set_and_print_seed();
	// const t_iv random_vector = create_rand_vector(10000, 1000000);
	const t_iv random_vector = input;
	const t_iv pair_vector = make_pairs_of_pairs(random_vector);

	const unsigned int biggest_smaller_power = calculate_biggest_block(pair_vector);

	// OS << "biggest_smaller_power " << biggest_smaller_power << EL;

	const unsigned int two_block_size = biggest_smaller_power / 2;
	t_iv one_swap_vector = pair_vector;
	block_swap(one_swap_vector.begin(), one_swap_vector.begin() + two_block_size, two_block_size);


	OS << random_vector << "\n\n";


	t_iv before(one_swap_vector);
	OS << before << EL;
	for (unsigned int block_size = two_block_size / 2; block_size > 0; block_size /= 2)
	{
		OS << block_size << " (blocksize), \n" << before << EL;
		block_vector bs_blocks(before, block_size);

		t_iv bs_all_a_s = bs_blocks.get_all_A_blocks();
		
		block_vector bs_all_a_s_BV(bs_all_a_s, block_size);
		
		bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);
		
		before.clear();
		before = bs_all_a_s_BV.getVector();
	}

	final_check_and_msg(before);


    {
        block_vector test1(input, 1);
        OS << "test1 = \n" << test1.getVector() << EL;
        for (unsigned int i = 1; i <= test1.max_A_i(); i++)
        {
            OS << "A_"<< i << " = " << test1.get_A(i) << EL;
        }
        OS << EL << EL;
        for (unsigned int i = 1; i <= test1.max_B_i(); i++)
        {
            OS << "B_" << i << " = " << test1.get_B(i) << EL;
        }
        OS << EL;
    }


	return 0;
}


