#!/bin/bash

IFS=','
iteration=0
total=0
while read f; do
    summation=0
    numberOfNumbers=0
    for number in $f; do
        (( summation = summation + number))
        (( numberOfNumbers = numberOfNumbers + 1))
    done

    (( total = total + summation))

    if [[ $numberOfNumbers != 0 ]]; then
        ((iteration = iteration + 1))
        echo "Line $iteration: $summation"
    fi
done < "$1"

(( average = total / iteration))
echo "Average: $average"