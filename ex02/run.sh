#! /bin/bash

get_seeded_random()
{
  seed="$1"
  openssl enc -aes-256-ctr -pass pass:"$seed" -nosalt \
    </dev/zero 2>/dev/null
}

SEED=$RANDOM
NUM=$((1 + $RANDOM % 10000))

echo "SEED = $SEED"
echo "NUM = $NUM"



./PmergeMe $(seq $NUM | gsort --random-source=<(get_seeded_random $SEED) -R  | tr '\n' ' ')