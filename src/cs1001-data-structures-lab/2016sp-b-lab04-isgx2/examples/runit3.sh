#!/bin/bash

if (( $# > 0 )); then
	g++ *.cpp -o "$1"
	exe="$1"
else
	g++ *.cpp
	exe=a.out
fi

if [[ $? -eq 0 ]]; then 
	./"$exe"
fi

