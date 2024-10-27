#include <iostream>
#include <vector>
#include <cstdlib>
#include "PmergeMe.hpp"

int main()
{
	set_and_print_seed();
	const t_iv random_vector = create_rand_vector(10000, 1000000);
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
		block_vector bs_blocks(before, block_size);

		t_iv bs_all_a_s = bs_blocks.get_all_A_blocks();
		
		block_vector bs_all_a_s_BV(bs_all_a_s, block_size);
		
		bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);
		
		before.clear();
		before = bs_all_a_s_BV.getVector();
		// OS << block_size << " " << before << EL;
	}

	final_check_and_msg(before);



	return 0;
}


