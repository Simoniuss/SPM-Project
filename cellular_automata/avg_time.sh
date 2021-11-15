#!/bin/bash

# Script to compute average time of multiple execution of ./game_of_life
# Arguments: number_executions rows columns steps parallel_degree


if [ "$#" -ne 5 ]; then
    echo "Illegal number of parameters: number_executions rows columns steps parallel_degree"
    exit
fi


for ((i = 0 ; i < $1 ; i++));
do
    ./game_of_life $2 $3 $4 $5
done | awk '{sum_seq += $2; sum_par += $4; sum_par_ff += $6} END {print "Tseq:",sum_seq/NR,"Tpar:",sum_par/NR,"Tpar_ff:",sum_par_ff/NR}'
