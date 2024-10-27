#include <iostream>
#include <vector>

#include <cstdlib>
#include <cassert>
#include <cmath>


#include "print_helper.hpp"

#define OS std::cout
#define EL std::endl

int main();

class block_vector;

class block_vector
{
private:
	t_iv _vector;
public:
	
	block_vector(const t_iv &other, const unsigned int &block_size_initializer);
	~block_vector();
	
	const unsigned int block_size;

	void insert_X_block(const unsigned int pos, const t_iv &block_vec);
	void binary_insert_block(const unsigned int k, const t_iv &block_vec);
	void binary_insert_all_B_s(const block_vector &paired_block_vector);

	t_iv get_A_block(const unsigned int i) const;
	t_iv get_B_block(const unsigned int i) const;
	t_iv get_X_block(const unsigned int i) const;
	t_iv get_all_A_blocks() const;

	unsigned int max_A_i(void) const;
	unsigned int max_B_i(void) const;

	int get_A(const unsigned int i) const;
	int get_B(const unsigned int i) const;
	int get_X(const unsigned int i) const;


	const t_iv& getVector() const {
		return _vector;
	}
};

block_vector::block_vector(const t_iv &other, const unsigned int &block_size_initializer): _vector(other), block_size(block_size_initializer)
{
	unsigned int num = block_size_initializer;
	while (num > 1)
	{
		if (num % 2 == 1)
		{
			std::cerr << "Provided Blocksize " << block_size_initializer << " is not a power of 2\n";
			throw std::exception();
		}
		num /= 2;
	}
}

block_vector::~block_vector()
{
}

void block_vector::insert_X_block(const unsigned int pos, const t_iv &block_vec)
{
	if (pos == 0 || pos > (_vector.size() / block_size) + 1)
	{
		std::cerr << "insert_X_block tried inserting at " << pos << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}

	_vector.insert(_vector.begin() + (pos - 1) * block_size, block_vec.begin(), block_vec.end());
}

// eg 7 -> 4, 2
// _1_2_3_4_5_6_7_
// eg 3 -> 
// _1_2_3_
// b_4 which has 7 options (for 8 rand num) can be inserted with 3 cmps
void block_vector::binary_insert_block(const unsigned int k, const t_iv &block_vec)
{
	unsigned int pos = std::pow(2, k - 1); // initial position 
	unsigned int step = pos / 2;
	const int leading_element = block_vec.at(0);
	// OS << "pos = " << pos << " step = " << step << " leading_elemet = " << EL;


	while (step > 0)
	{
		if (leading_element == 19){	OS << pos << " " << this->get_X(pos) << " " << EL; 	}
		if (this->get_X(pos) > leading_element)
			pos -= step;
		else
			pos += step;
		step /= 2;
	}

	if (leading_element == 19){	OS << pos << " " << this->get_X(pos) << " " << EL; 	}
	if (this->get_X(pos) < leading_element)
		pos += 1;
	else
		(void)0;

	// OS << k << " " << pos << " " << block_vec << EL;
	this->insert_X_block(pos, block_vec);
}

// operates on a blocked vector 
void block_vector::binary_insert_all_B_s(const block_vector &paired_block_vector)
{
	assert(this->block_size == paired_block_vector.block_size);
	
	unsigned int b_i_start = 1; 
	unsigned int b_i_end = 0; 
	unsigned int k_boundary = 31; // k upper bound chosen bc 32 bit int is at most 2^31 - 1

	for (unsigned int k = 1; k < k_boundary; k++)
	{
		// OS << "k = " << k << EL;
		b_i_start = ( std::pow(2, k + 1) + std::pow(-1, k) ) / 3;
		for (unsigned int index = b_i_start; index > b_i_end; index -= 1)
		{
			if (index > this->max_B_i())
				k_boundary = k;
			else
			{
				t_iv b_i = paired_block_vector.get_B_block(index);
				this->binary_insert_block(k, b_i);
			}
		}
		b_i_end = b_i_start;
	}
}


unsigned int block_vector::max_A_i(void) const
{
	return (_vector.size() / block_size) / 2;
}

unsigned int block_vector::max_B_i(void) const
{
	return ((_vector.size() / block_size) + 1) / 2;
}




int block_vector::get_A(const unsigned int i) const
{
	return _vector.at(2 * (i - 1) * block_size);
}

int block_vector::get_B(const unsigned int i) const
{
	return _vector.at(2 * (i - 1) * block_size + block_size);
}

int block_vector::get_X(const unsigned int i) const
{
	return _vector.at((i - 1) * block_size);
}


// one indexed acess for block A_1, A_2, ...
t_iv block_vector::get_A_block(const unsigned int i) const
{
	if (_vector.size() < 2 * (i - 1) * block_size + block_size)
	{
		std::cerr << "getA tried accessing element " << i << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}
	if (i == 0)
	{
		std::cerr << "getA is 1 indexed (0 is invalid) tried accessing element " << i << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}

	t_iv block;
	const t_iv::const_iterator block_start = _vector.begin() + 2 * (i - 1) * block_size; 
	block.insert(block.begin(), block_start, block_start + block_size);
	return block;
}

// one indexed acess for block B_1, B_2, ...
t_iv block_vector::get_B_block(const unsigned int i) const
{
	if (_vector.size() < 2 * (i) * block_size)
	{
		std::cerr << "get_B_block tried accessing element " << i << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}
	if (i == 0)
	{
		std::cerr << "get_A_block is 1 indexed (0 is invalid) tried accessing element " << i << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}

	t_iv block;
	const t_iv::const_iterator block_start = _vector.begin() + 2 * (i - 1) * block_size + block_size; 
	block.insert(block.begin(), block_start, block_start + block_size);
	return block;
}

// one indexed acess for block B_1, B_2, ...
t_iv block_vector::get_X_block(const unsigned int i) const
{
	if (_vector.size() < (i) * block_size)
	{
		std::cerr << "get_B_block tried accessing element " << i << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}
	if (i == 0)
	{
		std::cerr << "get_A_block is 1 indexed (0 is invalid) tried accessing element " << i << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}

	t_iv block;
	const t_iv::const_iterator block_start = _vector.begin() + (i - 1) * block_size; 
	block.insert(block.begin(), block_start, block_start + block_size);
	return block;
}


t_iv block_vector::get_all_A_blocks() const
{
	const unsigned int max_a_index = this->max_A_i();

	t_iv ret;
	for (unsigned int i = 1; i <= max_a_index; i += 1)
	{
		const t_iv a_i = this->get_A_block(i);
		ret.insert(ret.end(), a_i.begin(), a_i.end());
	}
	return ret;
}


// ----


int main()
{
	set_and_print_seed();
	const t_iv random_vector = create_rand_vector(11);
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














// -----------


void set_and_print_seed()
{
	// const unsigned int seed = time(NULL) % 1000;
	const unsigned int seed = 325;
	std::srand(seed);
	std::cout << "seed = " << seed << std::endl;
}

bool isSorted(const std::vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            return false; // Found an out-of-order element
        }
    }
    return true; // No out-of-order elements found
}

void final_check_and_msg(const t_iv &before)
{
	OS << before << EL;
	if (isSorted(before))
	{
		OS << "OK" << EL;
	}
	else
	{
		OS << "+---------+\n|         |\n|  ERROR  |\n|         |\n+---------+\n" << EL;
	}
}

void block_swap(t_iv::iterator a, t_iv::iterator b, const unsigned int block_size)
{
	for (size_t i = 0; i < block_size; i++)
	{
		const int tmp = *(a + i);

		*(a + i) = *(b + i);
		*(b + i) = tmp; 
	}
	
}

t_iv make_pairs_of_pairs(const t_iv &vector)
{
	t_iv new_vector(vector);

	unsigned int block_size = 1;
	unsigned int number_of_blocks;
	while (
		(number_of_blocks = vector.size() / block_size) > 1
	)
	{
		for (size_t i = 0; i + block_size < new_vector.size(); i += 2 * block_size)
		{
			if (new_vector.at(i) < new_vector.at(i + block_size))
				block_swap(new_vector.begin() + i, new_vector.begin() + i + block_size, block_size);
		}
		block_size *= 2;		
	}
	return new_vector;
}


std::vector<int> create_rand_vector()
{
	const unsigned int len = random() % 30;

	t_iv rand_vector;
	for (size_t i = 0; i < len; i++)
	{
		rand_vector.push_back(random() % 100);
	}
	return rand_vector;
}

std::vector<int> create_rand_vector(const unsigned int len)
{
	t_iv rand_vector;
	for (size_t i = 0; i < len; i++)
	{
		rand_vector.push_back(random() % 100);
	}
	return rand_vector;
}


unsigned int calculate_biggest_block(const t_iv &vector)
{
	const unsigned int vector_size = vector.size();
	unsigned int block_size = 1;
	while (vector_size / block_size > 1)
	{
		block_size *= 2;
	}
	return block_size;
}



std::ostream& operator<<(std::ostream& os, const std::vector<int> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		os << v.at(i);
		if (i % 2 == 0)	
			os << "==";
		else if (i % 4 == 1)
			os << "⋯⋯";
		else if (i % 8 == 3)
			os << "--";
		else
			os << "  ";
	}
	os << "\n";
	return os;
	
}