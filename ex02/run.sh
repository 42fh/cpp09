#! /bin/bash

get_seeded_random()
{
  seed="$1"
  openssl enc -aes-256-ctr -pass pass:"$seed" -nosalt \
    </dev/zero 2>/dev/null
}

SEED=$RANDOM
# NUM=$((1 + $RANDOM % 100))

NUM='29'

# SEED="17931"
# NUM="61"

# SEED='10314'
NUM='15'

# SEED="3413"
# NUM= "15"

NUM='7'
SEED= "24253"



echo "SEED = $SEED"
echo "NUM = $NUM"



./PmergeMe $(seq $NUM | gsort --random-source=<(get_seeded_random $SEED) -R  | tr '\n' ' ')