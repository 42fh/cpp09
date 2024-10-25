#include <iostream>
#include <cstdlib>
#include <vector>

#include "print_helper.hpp"

#define OS std::cout
#define EL std::endl

class block_vector
{
private:
	t_iv _vector;
public:
	
	block_vector(const t_iv &other, const unsigned int &block_size_initializer);
	~block_vector();
	
	const unsigned int block_size;

	void insert_X_block(const unsigned int pos, const t_iv &block_vec);

	t_iv get_A_block(const unsigned int i) const;
	t_iv get_B_block(const unsigned int i) const;
	t_iv get_X_block(const unsigned int i) const;

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
	if (pos == 0 || pos > _vector.size() / block_size)
	{
		std::cerr << "insert_X_block tried inserting at " << pos << " for blocksize " << block_size << " and vector size " << _vector.size() << " \n";
		throw std::exception();
	}

	_vector.insert(_vector.begin() + (pos - 1) * block_size, block_vec.begin(), block_vec.end());
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


// ----


int main(int argc, char const *argv[])
{
	set_and_print_seed();


	const t_iv random_vector = create_rand_vector(16);
	const t_iv pair_vector = make_pairs_of_pairs(random_vector);

	const unsigned int biggest_smaller_power = calculate_biggest_block(pair_vector);

	OS << "biggest_smaller_power " << biggest_smaller_power << EL;


	const unsigned int two_block_size = biggest_smaller_power / 2;
	t_iv one_swap_vector = pair_vector;
	block_swap(one_swap_vector.begin(), one_swap_vector.begin() + two_block_size, two_block_size);

	OS << random_vector << "\n\n";
	OS << pair_vector << "\n\n";
	OS << one_swap_vector << "\n\n";


	// block_vector demo
	/*
	{
		block_vector bv1(one_swap_vector, 4);
		OS << "block vect \n " << bv1.getVector(); 
		OS << "block A_1 = \n " << bv1.get_A_block(1); 
		OS << "block B_1 = \n " << bv1.get_B_block(1); 
		OS << "block A_2 = \n " << bv1.get_A_block(2); 
		OS << "block B_2 = \n " << bv1.get_B_block(2); 

		block_vector bv2(one_swap_vector, 16);
		OS << "block A_1 = \n " << bv2.get_A_block(1); 
	}
	*/


	block_vector four_blocks(one_swap_vector, 4); // four blocks of size four

	t_iv four_blocks_sorted;

	// blind chain
	t_iv a2 = four_blocks.get_A_block(2);	four_blocks_sorted.insert(four_blocks_sorted.begin(), a2.begin(), a2.end());
	t_iv a1 = four_blocks.get_A_block(1);	four_blocks_sorted.insert(four_blocks_sorted.begin(), a1.begin(), a1.end());
	t_iv b1 = four_blocks.get_B_block(1);	four_blocks_sorted.insert(four_blocks_sorted.begin(), b1.begin(), b1.end());

	// insert b2
	t_iv b2 = four_blocks.get_B_block(2);

	block_vector four_blocks_sorted_BV(four_blocks_sorted, 4);
	unsigned int pos = 2;
	if (four_blocks_sorted_BV.get_X(pos) > b2.front())
		pos -= 1;
	else
		pos += 1;
	
	if (four_blocks_sorted_BV.get_X(pos) > b2.front())
		pos += 0;
	else
		pos += 1;
	
	OS << "pos = " << pos << EL;
	four_blocks_sorted_BV.insert_X_block(pos, b2);
	// four_blocks_sorted.insert(four_blocks_sorted.begin() + (pos - 1) * 4, b2.begin(), b2.end());




	OS << four_blocks_sorted << EL;
	OS << four_blocks_sorted_BV.getVector() << EL;


	return 0;
}














// -----------


void set_and_print_seed()
{
	const unsigned int seed = time(nullptr) % 1000;
	std::srand(seed);
	std::cout << "seed = " << seed << std::endl;
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