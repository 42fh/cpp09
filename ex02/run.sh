#! /bin/bash

get_seeded_random()
{
  seed="$1"
  openssl enc -aes-256-ctr -pass pass:"$seed" -nosalt \
    </dev/zero 2>/dev/null
}

# SEED=$RANDOM
SEED='22755'
echo "SEED = $SEED"

./PmergeMe $(seq 9 | gsort --random-source=<(get_seeded_random $SEED) -R  | tr '\n' ' ')