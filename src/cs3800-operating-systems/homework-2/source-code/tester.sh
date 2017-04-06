#!/bin/sh
main="main.py"

declare -a algorithms=("clock" "lru" "fifo")
declare -a prepagings=("prepaging" "ondemand")

for prepaging in "${prepagings[@]}"; do
    for algorithm in "${algorithms[@]}"; do
        pageSize=1
        while [[ $pageSize -le 16 ]]; do
            python3 main.py programlist.txt commandlist.txt $pageSize $algorithm $prepaging 2> error.txt
        done
    done
done

