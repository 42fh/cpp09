#include "pme-deque.hpp"


block_deque::block_deque(const t_id &other, const unsigned int &block_size_initializer): _deque(other), block_size(block_size_initializer)
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

block_deque::~block_deque()
{
}

void block_deque::insert_X_block(const unsigned int pos, const t_id &block_deq)
{
    if (pos == 0 || pos > max_X_i() + 1)
	{
		std::cerr << "insert_X_block tried inserting at " << pos << " for blocksize " << block_size << " and deque size " << _deque.size() << " \n";
		std::cerr << "this->deque " << this->getDeque() << " block_deq = " << block_deq << EL;
        throw std::exception();
	}

	_deque.insert(_deque.begin() + (pos - 1) * block_size, block_deq.begin(), block_deq.end());
}

void block_deque::insert_raw(const t_id::const_iterator begin, const t_id::const_iterator end)
{
    _deque.insert(_deque.end(), begin, end);
}


// eg 7 -> 4, 2
// _1_2_3_4_5_6_7_
// eg 3 -> 
// _1_2_3_
// b_4 which has 7 options (for 8 rand num) can be inserted with 3 comparisons
void block_deque::binary_insert_block(const unsigned int k, const t_id &block_deq)
{
	unsigned int pos = std::pow(2, k - 1); // initial position 
	unsigned int step = pos / 2;
	const int leading_element = block_deq.at(0);
    const unsigned int upper_bound = max_X_i();
	// OS << "pos = " << pos << " step = " << step << " leading_element = " << EL;

	while (step > 0)
	{
		if (this->get_X(pos) > leading_element)
			pos -= step;
		else
			pos = std::min(pos + step, upper_bound) ;
		step /= 2;
	}

	if (this->get_X(pos) < leading_element)
		pos += 1;
	else
		(void)0;

	// OS << k << " " << pos << " " << block_deq << EL;
	this->insert_X_block(pos, block_deq);
}

// operates on a blocked deque 
void block_deque::binary_insert_all_B_s(const block_deque &paired_block_deque)
{
	assert(this->block_size == paired_block_deque.block_size);
	
	unsigned int b_i_start = 1; 
	unsigned int b_i_end = 0; 
	unsigned int k_boundary = 31; // k upper bound chosen bc 32 bit int is at most 2^31 - 1

	for (unsigned int k = 1; k < k_boundary; k++)
	{
		// OS << "k = " << k << EL;
		b_i_start = ( std::pow(2, k + 1) + std::pow(-1, k) ) / 3;
		for (unsigned int index = b_i_start; index > b_i_end; index -= 1)
		{
			if (index > paired_block_deque.max_B_i())
				k_boundary = k;
			else
			{
                // OS << "index = " << index << " max B_i,i= " << paired_block_deque.max_B_i() << EL;
				t_id b_i = paired_block_deque.get_B_block(index);
				this->binary_insert_block(k, b_i);
			}
		}
		b_i_end = b_i_start;
	}
}


unsigned int block_deque::max_A_i(void) const
{
	return (_deque.size() / block_size) / 2;
}

unsigned int block_deque::max_B_i(void) const
{
	return ((_deque.size() / block_size) + 1) / 2;
}

unsigned int block_deque::max_X_i(void) const
{
	return ((_deque.size() / block_size));
}


int block_deque::get_A(const unsigned int i) const
{
    if (i == 0 || i > this->max_A_i())
        throw std::runtime_error("get_A tried accessing out of range index");
	return _deque.at(2 * (i - 1) * block_size);
}

int block_deque::get_B(const unsigned int i) const
{
    if (i == 0 || i > this->max_B_i())
        throw std::runtime_error("get_A tried accessing out of range index");
    if (i == this->max_B_i() && max_B_i() > max_A_i())
    	return _deque.at(2 * (i - 1) * block_size);
    else
    	return _deque.at(2 * (i - 1) * block_size + block_size);
}

int block_deque::get_X(const unsigned int i) const
{
    if (i == 0 || i > max_X_i())
        throw std::runtime_error("get_X tried accessing out of range index");
	return _deque.at((i - 1) * block_size);
}

// one indexed access for block A_1, A_2, ...
t_id block_deque::get_A_block(const unsigned int i) const
{
	if (i == 0 || i > max_A_i())
	{
		std::cerr << "getA is 1 indexed (0 is invalid) tried accessing element " << i << " for blocksize " << block_size << " and deque size " << _deque.size() << " \n";
		throw std::exception();
	}

	t_id block;
	const t_id::const_iterator block_start = _deque.begin() + 2 * (i - 1) * block_size; 
	block.insert(block.begin(), block_start, block_start + block_size);
	return block;
}

// one indexed access for block B_1, B_2, ...
t_id block_deque::get_B_block(const unsigned int i) const
{
	if (i == 0 || i > max_B_i())
	{
		std::cerr << "get_A_block is 1 indexed (0 is invalid) tried accessing element " << i << " for blocksize " << block_size << " and deque size " << _deque.size() << " \n";
		throw std::exception();
	}

	t_id block;
    // note the elements are layed out in the deque like this: (special case odd elements), eg. 5:
    // A_1 B_1 A_2 B_2 B_3 (so the last element is B_3!)    
    const t_id::const_iterator block_start = 
        (i == max_B_i() && max_B_i() > max_A_i()) ? 
            _deque.begin() + 2 * (i - 1) * block_size 
            : _deque.begin() + 2 * (i - 1) * block_size + block_size; 

	block.insert(block.begin(), block_start, block_start + block_size);
	return block;
}

// one indexed access for block B_1, B_2, ...
t_id block_deque::get_X_block(const unsigned int i) const
{
	if (i == 0 || i > max_X_i())
	{
		std::cerr << "get_A_block is 1 indexed (0 is invalid) tried accessing element " << i << " for blocksize " << block_size << " and deque size " << _deque.size() << " \n";
		throw std::exception();
	}

	t_id block;
	const t_id::const_iterator block_start = _deque.begin() + (i - 1) * block_size; 
	block.insert(block.begin(), block_start, block_start + block_size);
	return block;
}


t_id block_deque::get_all_A_blocks() const
{
	const unsigned int max_a_index = this->max_A_i();

	t_id ret;
	for (unsigned int i = 1; i <= max_a_index; i += 1)
	{
		const t_id a_i = this->get_A_block(i);
		ret.insert(ret.end(), a_i.begin(), a_i.end());
	}
	return ret;
}


// main()














// -----------


void set_and_print_seed()
{
	const unsigned int seed = time(NULL) % 1000;
	// const unsigned int seed = 325;
	std::srand(seed);
	std::cout << "seed = " << seed << std::endl;
}

bool isSorted(const std::deque<int>& deq) {
    for (size_t i = 1; i < deq.size(); ++i) {
        if (deq[i] < deq[i - 1]) {
            return false; // Found an out-of-order element
        }
    }
    return true; // No out-of-order elements found
}

void final_check_and_msg(const t_id &before)
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

void block_swap(t_id::iterator a, t_id::iterator b, const unsigned int block_size)
{
	for (size_t i = 0; i < block_size; i++)
	{
		const int tmp = *(a + i);

		*(a + i) = *(b + i);
		*(b + i) = tmp; 
	}
	
}

t_id make_pairs_of_pairs(const t_id &deque)
{
	t_id new_deque(deque);

	unsigned int block_size = 1;
	unsigned int number_of_blocks;
	while (
		(number_of_blocks = deque.size() / block_size) > 1
	)
	{
		for (size_t i = 0; i + 2 * block_size <= new_deque.size(); i += 2 * block_size)
		{
			if (new_deque.at(i) < new_deque.at(i + block_size))
				block_swap(new_deque.begin() + i, new_deque.begin() + i + block_size, block_size);
		}
		block_size *= 2;		
	}
	return new_deque;
}


std::deque<int> create_rand_deque()
{
	const unsigned int len = random() % 30;

	t_id rand_deque;
	for (size_t i = 0; i < len; i++)
	{
		rand_deque.push_back(random() % 100);
	}
	return rand_deque;
}

std::deque<int> create_rand_deque(const unsigned int len)
{
	t_id rand_deque;
	for (size_t i = 0; i < len; i++)
	{
		rand_deque.push_back(random() % 100);
	}
	return rand_deque;
}

std::deque<int> create_rand_deque(const unsigned int len, const unsigned int max_val)
{
	t_id rand_deque;
	for (size_t i = 0; i < len; i++)
	{
		rand_deque.push_back(random() % max_val);
	}
	return rand_deque;
}


unsigned int calculate_biggest_block(const t_id &deque)
{
	const unsigned int deque_size = deque.size();
	unsigned int block_size = 1;
	while (deque_size / block_size > 1)
	{
		block_size *= 2;
	}
	return block_size;
}



std::ostream& operator<<(std::ostream& os, const std::deque<int> &d)
{
	size_t i = 0;
	for (; i < d.size() && i < 14; i++)
	{
		os << d.at(i);
		if (i % 2 == 0)	
			os << "==";
		else if (i % 4 == 1)
			os << "⋯⋯";
		else if (i % 8 == 3)
			os << "--";
		else
			os << "  ";
	}
	if (i < d.size())
		os << "... (" << d.size() << " more)" << EL;
	os << "\n";
	return os;
	
}