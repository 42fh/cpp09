#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include "PmergeMe.hpp"
#include <iomanip>

bool hasDuplicates(const std::vector<int>& other) {
    t_iv vec(other);
    std::sort(vec.begin(), vec.end());
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] == vec[i - 1]) {
            return true;
        }
    }
    return false;
}

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


	const t_iv random_vector = input;
	const t_iv pair_vector = make_pairs_of_pairs(random_vector);

    OS << "pair_vector\n " << pair_vector << EL;

	const unsigned int biggest_smaller_power = calculate_biggest_block(pair_vector);

	t_iv before(pair_vector);
	OS << before << EL;
	for (unsigned int block_size = biggest_smaller_power / 2; block_size > 0; block_size /= 2)
	{
        if (hasDuplicates(before))
            OS << "ERROR, duplicates!\n"; 

		block_vector bs_blocks(before, block_size);
		t_iv bs_all_a_s = bs_blocks.get_all_A_blocks();
		block_vector bs_all_a_s_BV(bs_all_a_s, block_size);
		
		bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);     
        const int delta = before.size() - bs_all_a_s_BV.getVector().size();
        bs_all_a_s_BV.insert_raw(before.end() - delta, before.end());

		before.clear();
		before = bs_all_a_s_BV.getVector();
	}

	final_check_and_msg(before);

    main2(c, v);

	return 0;
}

// validate_input_deque
static std::deque<int> validate_input_deque(int c, char **v)
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

int main2(int c, char **v)
{
    if (c < 2){
        std::cerr << "Error: no input provided\n"; return(1); }

    std::deque<int> input;
    try {
        input = validate_input_deque(c, v);
    }
    catch (std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "provided input:\n" << input << '\n';


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

		block_deque bs_blocks(before, block_size);
		t_id bs_all_a_s = bs_blocks.get_all_A_blocks();
		block_deque bs_all_a_s_BV(bs_all_a_s, block_size);
		
		bs_all_a_s_BV.binary_insert_all_B_s(bs_blocks);
     
        const int delta = before.size() - bs_all_a_s_BV.getDeque().size();
        bs_all_a_s_BV.insert_raw(before.end() - delta, before.end());

		before.clear();
		before = bs_all_a_s_BV.getDeque();
	}

	final_check_and_msg(before);

	return 0;
}


