#pragma once

typedef std::vector<int> t_iv;

std::ostream& operator<<(std::ostream& os, const std::vector<int> &v);

std::vector<int> create_rand_vector();
std::vector<int> create_rand_vector(const unsigned int len);
t_iv make_pairs_of_pairs(const t_iv &vector);
void set_and_print_seed();
void block_swap(t_iv::iterator a, t_iv::iterator b, const unsigned int block_size);
unsigned int calculate_biggest_block(const t_iv &vector);


