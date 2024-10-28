#include <iostream>
#include <deque>
#include <set>
#include <cstdlib>
#include "pme-deque.hpp"
#include <iomanip>

bool hasDuplicates(const std::deque<int>& other) {
    t_id deq(other);
    std::sort(deq.begin(), deq.end());
    for (size_t i = 1; i < deq.size(); ++i) {
        if (deq[i] == deq[i - 1]) {
            return true;
        }
    }
    return false;
}

static bool is_digit(char *str)
{
    while (*str)
    {
        if (std::isdigit(*str) == 0) return (false);
        str++;
    }
    return (true);
}

static std::deque<int> validate_input(int c, char **v)
{
    std::deque<int> ret;

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


    std::deque<int> input;
    try {
        input = validate_input(c, v);
    }
    catch (std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "provided input:\n" << input << '\n';

	// ---- old vs new

	// set_and_print_seed();
	// const t_id random_deque = create_rand_deque(10000, 1000000);


	const t_id random_deque = input;
	const t_id pair_deque = make_pairs_of_pairs(random_deque);

    OS << "pair_deque\n " << pair_deque << EL;

	const unsigned int biggest_smaller_power = calculate_biggest_block(pair_deque);

	t_id before(pair_deque);
	OS << before << EL;
	for (unsigned int block_size = biggest_smaller_power / 2; block_size > 0; block_size /= 2)
	{
        if (hasDuplicates(before))
            OS << "ERROR, duplicates!\n"; 
		// OS << block_size << " (blocksize) | num elements " << before.size() << "\n" << before << EL;

		block_deque bs_blocks(before, block_size);
        // OS << "bs_block \n" << bs_blocks.getDeque() << EL;

		t_id bs_all_a_s = bs_blocks.get_all_A_blocks();
        // OS << "bs_all_a_s \n" << bs_all_a_s << EL;

		block_deque bs_all_a_s_BV(bs_all_a_s, block_size);
        // OS << "bs_all_a_s_BV \n" << bs_all_a_s_BV.getDeque() << EL;

		
		bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);
        // OS << "bs_all_a_s_BV binary inserted \n" << bs_all_a_s_BV.getDeque() << EL;
     
        const int delta = before.size() - bs_all_a_s_BV.getDeque().size();
        bs_all_a_s_BV.insert_raw(before.end() - delta, before.end());

		before.clear();
		before = bs_all_a_s_BV.getDeque();
	}

	final_check_and_msg(before);


    // {
    //     block_deque test1(input, 2);
    //     OS << "test1 = \n" << test1.getDeque() << EL;
    //     for (unsigned int i = 1; i <= test1.max_A_i(); i++)
    //     {
    //         OS << "A_"<< i << " = " << test1.get_A(i) << EL;
    //     }
    //     OS << EL << EL;
    //     for (unsigned int i = 1; i <= test1.max_B_i(); i++)
    //     {
    //         OS << "B_" << i << " = " << test1.get_B(i) << EL;
    //     }
    //     OS << EL;
    // }


	return 0;
}