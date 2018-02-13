#!/bin/bash

# Here is a very simple bash script for your benefit
# This script compiles and runs AI_helper.cpp
# You will need to modify this script to make it work for you.
# You may of course re-write your own run.sh, but it will need
#   to accomplish the same result.

# Compile with C++11 and other flags
g++ -std=c++11 -W -Wall -pedantic-errors AI_helper.cpp -o AI_helper

# Run program for all puzzle files in current directory
for puzzle in puzzle*.txt; do
  solution="solution"$(echo $puzzle | tr -dc "0-9")".txt"
  ./AI_helper $puzzle $solution
done
