#!/bin/bash

# DO NOT MODIFY THIS SCRIPT

# This script is to help you test your AI and for grading purposes. Your code will be compiled and ran by this script.

LANG=$1
TEST_ARGS="${@:2}"

cd $LANG
make
./testRun $TEST_ARGS &
./testRun $TEST_ARGS > /dev/null

# DO NOT MODIFY THIS SCRIPT