#! /bin/bash

get_seeded_random()
{
  seed="$1"
  openssl enc -aes-256-ctr -pass pass:"$seed" -nosalt \
    </dev/zero 2>/dev/null
}

SEED=$RANDOM
echo "SEED = $SEED"

./PmergeMe $(seq 100 | sort --random-source=<(get_seeded_random $SEED) -R  | tr '\n' ' ')