#!/bin/bash

# Script to compute computation time, in different conditions, of game_of_life.cpp
# 1) Average time per step. Fixed dimension (500x500), fixed parDegree (8).
# 2) Total time with different dimensions. Fixed steps (5), fixed parDegree (8).
# 3) Total time with different parDegree. Fixed dimension (1000x1000), fixed steps (5).

# Different steps
STEPS=(1 10 20 50 100)

# Different square matrices dimensions
DIMENSIONS=(10 100 1000 2000)

# Different number of workers
WORKERS=(1 2 4 8 16 32 64 128 256)

# Number of repetitions of each call to compute the average time
N=5

# Test 1) Average time per step
# $i number of steps
echo "Step script starts..."
for i in ${STEPS[@]};
do
    for ((j = 0 ; j < $N ; j++));
    do
        # ./game_of_life rows columns steps parallel_degree
        ./game_of_life 500 500 $i 8

    # sum+=$token/$i average time per step for each iteration. (DO NOT DELETE quotes in "'${i}'")
    # save the average of N iterations in step.txt
    done | awk '{sum_seq += $2/"'${i}'"; sum_par += $4/"'${i}'"; sum_par_ff += $6/"'${i}'"} END {print "'${i}'",sum_seq/NR,sum_par/NR,sum_par_ff/NR >> "step.txt"}'
done
echo "...step script completed!"


# Test 2) Total time per dimensions
# $i dimension size
echo "Dimension script starts..."
for i in ${DIMENSIONS[@]};
do
    for ((j = 0 ; j < $N ; j++));
    do
        # ./game_of_life rows columns steps parallel_degree
        ./game_of_life $i $i 5 8

    # sum+=$token total time for each iteration
    # save the average of N iterations in dimension.txt
    done | awk '{sum_seq += $2; sum_par += $4; sum_par_ff += $6} END {print "'${i}'",sum_seq/NR,sum_par/NR,sum_par_ff/NR >> "dimension.txt"}'
done
echo "...dimension script completed!"


# Test 3) Total time per nworkers
# $i parallel degree
echo "Parallel degree script starts..."
for i in ${WORKERS[@]};
do
    for ((j = 0 ; j < $N ; j++));
    do
        # ./game_of_life rows columns steps parallel_degree
        ./game_of_life 1000 1000 5 $i

    # sum+=$token total time for each iteration
    # save the average of N iterations in time.txt
    done | awk '{sum_seq += $2; sum_par += $4; sum_par_ff += $6} END {print "'${i}'",sum_seq/NR,sum_par/NR,sum_par_ff/NR >> "time.txt"}'
done
echo "...parallel degree script completed!"
