#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <cassert>
#include <cstdlib>


#define OS std::cout
#define EL std::endl

class block_vector;

typedef std::vector<int> t_iv;

std::ostream& operator<<(std::ostream& os, const std::vector<int> &v);

std::vector<int> create_rand_vector();
std::vector<int> create_rand_vector(const unsigned int len);
std::vector<int> create_rand_vector(const unsigned int len, const unsigned int max_val);
t_iv make_pairs_of_pairs(const t_iv &vector);
void set_and_print_seed();
bool isSorted(const std::vector<int>& vec);
void final_check_and_msg(const t_iv &before);
void block_swap(t_iv::iterator a, t_iv::iterator b, const unsigned int block_size);
unsigned int calculate_biggest_block(const t_iv &vector);

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
    void insert_raw(const t_iv::const_iterator begin, const t_iv::const_iterator end);

	t_iv get_A_block(const unsigned int i) const;
	t_iv get_B_block(const unsigned int i) const;
	t_iv get_X_block(const unsigned int i) const;
	t_iv get_all_A_blocks() const;

	unsigned int max_A_i(void) const;
	unsigned int max_B_i(void) const;
	unsigned int max_X_i(void) const;

	int get_A(const unsigned int i) const;
	int get_B(const unsigned int i) const;
	int get_X(const unsigned int i) const;


	const t_iv& getVector() const {
		return _vector;
	}
};


class block_deque;

typedef std::deque<int> t_id;

std::ostream& operator<<(std::ostream& os, const std::deque<int> &d);

std::deque<int> create_rand_deque();
std::deque<int> create_rand_deque(const unsigned int len);
std::deque<int> create_rand_deque(const unsigned int len, const unsigned int max_val);
t_id make_pairs_of_pairs(const t_id &deque);
void set_and_print_seed();
bool isSorted(const std::deque<int>& deq);
void final_check_and_msg(const t_id &before);
void block_swap(t_id::iterator a, t_id::iterator b, const unsigned int block_size);
unsigned int calculate_biggest_block(const t_id &deque);

class block_deque
{
private:
	t_id _deque;
public:
	
	block_deque(const t_id &other, const unsigned int &block_size_initializer);
	~block_deque();
	
	const unsigned int block_size;

	void insert_X_block(const unsigned int pos, const t_id &block_deq);
	void binary_insert_block(const unsigned int k, const t_id &block_deq);
	void binary_insert_all_B_s(const block_deque &paired_block_deque);
    void insert_raw(const t_id::const_iterator begin, const t_id::const_iterator end);

	t_id get_A_block(const unsigned int i) const;
	t_id get_B_block(const unsigned int i) const;
	t_id get_X_block(const unsigned int i) const;
	t_id get_all_A_blocks() const;

	unsigned int max_A_i(void) const;
	unsigned int max_B_i(void) const;
	unsigned int max_X_i(void) const;

	int get_A(const unsigned int i) const;
	int get_B(const unsigned int i) const;
	int get_X(const unsigned int i) const;


	const t_id& getDeque() const {
		return _deque;
	}
};