#!/bin/bash

if [ ! -d "env" ]; then
    virtualenv ./env
    pip3 install -r requirements.txt
fi

source ./env/bin/activate

# Run program for all puzzle files in current directory
for puzzle in puzzle*.txt; do
  solution="solution"$(echo $puzzle | tr -dc "0-9")".txt"
  python3 -O src/main.py $puzzle --solution_path=$solution
done

deactivate
